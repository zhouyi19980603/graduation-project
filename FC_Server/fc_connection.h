#ifndef FC_CONNECTION_H
#define FC_CONNECTION_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace boost::asio;

class FC_Server;
class FC_Message;
class FC_Message_Handle;

class FC_Connection
{
public:
    FC_Connection(FC_Server* _server, io_service* service);
    ~FC_Connection();
    tcp::socket* get_socket();
    void read(); 
    void write(FC_Message* msg);
private:
    //read about
    void read_header();
    void read_body();
    void on_read_header(const boost::system::error_code& err);
    void on_read_body(const boost::system::error_code& err);
    //write about
    void on_wirte(FC_Message* message,const boost::system::error_code&err);
private:
    FC_Server* _server = nullptr;
    tcp::socket* _sock = nullptr;
    io_service* _service = nullptr;
    FC_Message* _recv_mess = nullptr;
    FC_Message_Handle* _message_handle = nullptr;
};

#endif // FC_CONNECTION_H
