#ifndef FC_CONNECTION_H
#define FC_CONNECTION_H

#include <boost/asio.hpp>

#define FC_TCP_PORT 56781
#define FC_TCP_ADDRESS "127.0.0.1"

using boost::asio::ip::tcp;
using boost::asio::io_service;
using boost::asio::posix::stream_descriptor;//io in stdin/stdout

class FC_Client;
class FC_Message;
class FC_Message_Handle;

class FC_Connection
{
public:
    FC_Connection(FC_Client* client);
    ~FC_Connection();
    void write(std::vector<std::string> msg); // display input write
    void write(FC_Message* message);//write message
private:
    //connect about
    void start_connect(); //connect to server
    void on_connect(const boost::system::error_code&err); //connect callback

    //read about
    void read(); // read from server
    void read_header();//read message header
    void read_body();//read message body
    void on_read_header(const boost::system::error_code&err); //read_header callback
    void on_read_body(const boost::system::error_code&err);  //read_body callback

    //write about
    void on_wirte(FC_Message* message,const boost::system::error_code&err); //write callback

    //test function
    void on_wirte(const boost::system::error_code&err);
    void on_read(const boost::system::error_code&err);

    //should not be included by this module
    char* encode_content(unsigned dest,unsigned src,char* msg);
private:

    FC_Client* _client = nullptr;
    tcp::socket* _socket = nullptr;
    io_service* _service = nullptr;
    FC_Message* _recv_message = nullptr;
    FC_Message_Handle* _message_handle = nullptr;

};

#endif // FC_CONNECTION_H
