#include "fc_connection.h"
#include "fc_message.h"
#include "fc_client.h"
#include "fc_message_handle.h"
#include "fc_header.h"

#include <boost/bind.hpp>
#include <QDebug>
#include<iostream>



using namespace boost::asio;
//using std::string;
/*
 * 当消息来临时,
 * 	1.读取message_header
 * 	2.解析message_header 获得message_body_length
 * 	3.读取 message_body
 * 	4.根据 message_type 处理message
 */

//==============================================
//  public function
//==============================================


FC_Connection::FC_Connection(FC_Client* client):_client(client)
{
    this->_service = this->_client->get_logic_service();
    this->_socket = new tcp::socket(*_service);
    this->_recv_message = new FC_Message;
    this->_message_handle = new FC_Message_Handle(_client);
    this->start_connect();
}
FC_Connection::~FC_Connection(){
    delete this->_message_handle;
    delete this->_recv_message;
    delete this->_socket;
}
void FC_Connection::write(std::vector<std::string> msg){
    int type1 = FC_TEXT_MEG;
    int type2 = FC_GROUP_TEXT_MEG;
    string content = msg.at(0)+msg.at(1)+msg.at(3);
    const char* body = this->_message_handle->text_body(content.c_str());
    if(msg.at(1) == "@56789"){
        FC_Message* message = this->_message_handle->
                generate_message(type2, body);
        this->write(message);
    }else{


        FC_Message* message = this->_message_handle->
                generate_message(type1, body);
        this->write(message);
    }

}

//==============================================
//  private function
//==============================================


//connect about
void FC_Connection::start_connect(){
    tcp::endpoint ep(ip::address::from_string(FC_TCP_ADDRESS),FC_TCP_PORT);
    this->_socket->async_connect(ep,boost::bind(&FC_Connection::on_connect,this,_1));
}
//回调函数
void FC_Connection::on_connect(const boost::system::error_code&err){
    if(!err){
        this->read();
    }else{
        //error handle
        if(err==boost::asio::error::connection_refused){
            qDebug() << "server not open";
            exit(err.value());
        }else{
            qDebug() << "on_connect: " << err.message().data() << " " <<  err.value();
            exit(err.value());
        }
    }
}

//read about
void FC_Connection::read(){ // read from server
    std::cout<<"test read()";
    this->read_header();
}
void FC_Connection::read_header(){
    std::cout<<"test read_header()\n";
    async_read(*this->_socket,buffer(_recv_message->header(), _recv_message->header_length()),bind(&FC_Connection::on_read_header,this,_1));
}
void FC_Connection::read_body(){
    std::cout<<"test read_body()";
    async_read(*this->_socket,buffer(_recv_message->body(), _recv_message->body_length()),bind(&FC_Connection::on_read_body,this,_1));

}
void FC_Connection::on_read_header(const boost::system::error_code&err){
    if(!err){
        //handle header and continue read body;
        this->_message_handle->handle_header(this->_recv_message);
        this->read_body();
    }else{
        //error handle
        if(err==boost::asio::error::eof){
            qDebug() << "server close \n";
            this->_socket->close();
            exit(err.value());
        }
        else{
            qDebug() << "on_read_header:" << err.value() << err.message().data();
            exit(err.value());
        }
    }
}
void FC_Connection::on_read_body(const boost::system::error_code&err){
    if(!err){
        //handle body and read another message header;

        //here use the same message to receive new message.
        this->_message_handle->handle_body(this->_recv_message);
        this->_recv_message = new FC_Message;
        this->read_header();

    }else{
        //error handle
        if(err==boost::asio::error::eof){
            qDebug() << "client close";
            this->_socket->close();
            exit(err.value());
        }
        else{
            qDebug() << "on_read_body:" << err.value() << err.message().data();
            exit(err.value());
        }
    }
}

//write about
void FC_Connection::write(FC_Message* message){
    unsigned len = message->mess_length();
    try {
        this->_socket->async_write_some(buffer(message->header(),len),boost::bind(&FC_Connection::on_wirte,this,message,_1));
    } catch (boost::system::system_error e) {
        qDebug() << "write:" <<e.code().message().data();
    }
}
void FC_Connection::on_wirte(FC_Message* message,const boost::system::error_code&err){
    delete message;
    if(!err){
        qDebug() << "write successfully";
    }else{
        qDebug() << "on_write: "<<err.message().data();
        exit(err.value());
    }
}


//test function
void FC_Connection::on_wirte(const boost::system::error_code&err){
    if(!err){
        qDebug() << "write successfully";
    }else{
        qDebug() << "on_write: "<<err.message().data();
        exit(err.value());
    }
}
void FC_Connection::on_read(const boost::system::error_code&err){
    if(!err){
        this->read();
    }else{
        if (err==boost::asio::error::eof){//end of file
            qDebug() << "server close";
            this->_socket->close();
            exit(err.value());
        }else{
            qDebug() << "on_read: "<<err.message().data();
            exit(err.value());
        }
    }
}

//other module
char* FC_Connection::encode_content(unsigned dest,unsigned src,char* msg){
    unsigned dest_size = sizeof (dest);
    unsigned src_size = sizeof (src);
    unsigned msg_size = strlen(msg)+1;
    unsigned total_size = dest_size+src_size+msg_size;
    char* res = (char*)malloc(total_size);
    memset(res,0,total_size);
    memcpy(res,&dest,dest_size);
    memcpy(res+dest_size,&src,src_size);
    memcpy(res+dest_size+src_size,msg,msg_size);
    return res;
}

//other function
void decode_content(char*content,unsigned len){
    unsigned dest;
    unsigned src;
    char* msg;
    memcpy(&dest,content,sizeof (unsigned));
    memcpy(&src,content+sizeof (unsigned),sizeof (unsigned));
    memcpy(&msg,content+sizeof (unsigned)*2,len-sizeof (unsigned)*2);
}
char* encode_int_to_char(unsigned i){
    char *c;
    c = (char*)malloc(5);
    c[0] = i>>24;
    c[1] = i>>16;
    c[2] = i>>8;
    c[3] = i;
    c[4] = '\0';
    return c;
}
unsigned encode_char_to_int(char* c){
    unsigned result=0;
    for(int i=0;i!=4;++i){
        result <<=8;
        result +=c[i];
    }
    return result;
}
