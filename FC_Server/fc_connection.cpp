#include <boost/bind.hpp>
#include "fc_connection.h"
#include "fc_server.h"
#include "fc_message.h"
#include "fc_message_handle.h"
#include <iostream>
#include <QDebug>

//==============================================
//  public function
//==============================================


FC_Connection::FC_Connection(FC_Server* server, io_service* service)
    :_server(server),_service(service)
{
    this->_sock = new tcp::socket(*service);
    this->_recv_mess = new FC_Message;
    this->_message_handle = new FC_Message_Handle(this->_server,this);
}
FC_Connection::~FC_Connection(){
    delete this->_sock;
    delete this->_recv_mess;
    delete this->_message_handle;
}

tcp::socket* FC_Connection::get_socket(){
    return this->_sock;
}

void FC_Connection::read(){
    qDebug()<<"read";
    read_header();
}
void FC_Connection::write(FC_Message* message){
   // qDebug() <<"json message 打印:"<<message->body();
    unsigned len = message->mess_length();

    try {
        async_write(*this->_sock,buffer(message->header(),len),boost::bind(&FC_Connection::on_wirte,this,message,_1));
    } catch (boost::system::system_error e) {
        qDebug() << "write:" <<e.code().message().data();
    }
}

//==============================================
//  private function
//==============================================

//read about
void FC_Connection::read_header(){
    async_read(*this->_sock,buffer(_recv_mess->header(),_recv_mess->header_length()),bind(&FC_Connection::on_read_header,this,_1));
}
void FC_Connection::read_body(){
    async_read(*this->_sock,buffer(_recv_mess->body(),_recv_mess->body_length()),bind(&FC_Connection::on_read_body,this,_1));
}
void FC_Connection::on_read_header(const boost::system::error_code& err){
    if(err){
        //error handle
        if(err==boost::asio::error::eof){
            qDebug() << "client close";
            this->_server->erase_connection(this);
        }
        else{
            qDebug() << "on_read_header:" << err.value() << err.message().data();
            exit(err.value());
        }
    }else{
        qDebug()<<"on_read_header";
        this->_message_handle->handle_header(this->_recv_mess); //set size
        this->read_body();
    }
}
void FC_Connection::on_read_body(const boost::system::error_code& err){
    if(err){
        //error handle
        if(err==boost::asio::error::eof){
            qDebug() << "client close";
            this->_server->erase_connection(this);
        }
        else{
            qDebug() << "on_read_body:" << err.value() << err.message().data();
            exit(err.value());
        }
    }else{
        qDebug()<<"on_read_body";
        //handle body and read another message header;
        this->_message_handle->handle_body(this->_recv_mess);
        this->_recv_mess = new FC_Message;
        this->read_header();
    }
}

//write about
void FC_Connection::on_wirte(FC_Message* message,const boost::system::error_code&err){
    delete message;

    if(!err){
        qDebug() << "write successfully";
    }else{
        qDebug() << "on_write: "<<err.message().data();
        exit(err.value());
    }
}
