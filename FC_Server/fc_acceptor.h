#ifndef FC_ACCEPTOR_H
#define FC_ACCEPTOR_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace boost::asio;

class FC_Server;
class FC_Connection;

class FC_Acceptor
{
public:
    FC_Acceptor(FC_Server* server,int port);
    ~FC_Acceptor();

private:
    void start_accept();
    void on_accept(const boost::system::error_code &err/*,tcp::socket peer*/);

private:
    FC_Server* _server = nullptr;
    tcp::endpoint* _ep = nullptr;
    tcp::acceptor* _acceptor = nullptr;
    FC_Connection* _connection = nullptr;
};

#endif // FC_ACCEPTOR_H
