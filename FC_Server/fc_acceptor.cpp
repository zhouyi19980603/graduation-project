#include <boost/bind.hpp>
#include <QDebug>
#include "fc_acceptor.h"
#include "fc_server.h"
#include "fc_connection.h"

FC_Acceptor::FC_Acceptor(FC_Server* server,int port):_server(server)
{
    this->_ep = new tcp::endpoint(tcp::v4(),port);
    io_service* service = _server->get_acceptor_service();
    this->_acceptor = new tcp::acceptor(*service,*_ep);

    //set acceptor reuse address
    tcp::socket::reuse_address ra(true);
    boost::system::error_code err;
    this->_acceptor->set_option(ra,err);
    if(err){
        qDebug() << "FC_Acceptor"<<err.message().data();
        exit(err.value());
    }

    //get a connection;
    this->_connection = this->_server->get_connection();

    start_accept();
}

FC_Acceptor::~FC_Acceptor(){
    delete this->_ep;
    delete this->_acceptor;
}

void FC_Acceptor::start_accept(){
    auto sock = this->_connection->get_socket();

    boost::system::error_code err;
    _acceptor->async_accept(*sock,boost::bind(&FC_Acceptor::on_accept,this,_1),&err);
    if(err){
        qDebug() <<"start_accept: "<< err.message().data();
        exit(err.value());
    }
}

void FC_Acceptor::on_accept(const boost::system::error_code &err/*,tcp::socket peer*/){
    if(err){
        //handle error
        qDebug() <<"on_accept: "<< err.message().data();
        exit(err.value());
    }else{
        qDebug() << "accept_arrive";
        //put this handled by server
        this->_server->handle_connected(this->_connection);
        //get new socket
        this->_connection = this->_server->get_connection();
        //continue accept
        start_accept();
    }
}
