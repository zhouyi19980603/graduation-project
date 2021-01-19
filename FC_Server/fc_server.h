#ifndef FC_SERVER_H
#define FC_SERVER_H

#include <boost/asio.hpp>
#include <vector>
#include <unordered_map>
#include <queue>
#include <QVariant>

using boost::asio::io_service;
using std::vector;
using std::unordered_map;
using std::string;

class FC_Thread_Pool;
class FC_Acceptor;
class FC_Connection;
class FC_Message;
class DbBroker;

class FC_Server
{
public:
    FC_Server(int thread_num,int port);
    ~FC_Server();

    //thread_pool about
    io_service* get_logic_service(); //get socket io_service
    io_service* get_acceptor_service(); // get acceptor io_service

    //connection about
    FC_Connection* get_connection(); //get new connection
    void handle_connected(FC_Connection* connection);//
    void erase_connection(FC_Connection* connection);//remove closed connect

    //向客户端发送消息
    void forward_group_message(string groupId,string senderId,FC_Message* msg);                 //群消息
    void forward_message(string id,FC_Message* msg);       //点对点消息
    
    //profile about
    void add_identified(string,FC_Connection*);

    //setter getter
    void set_accounts(const string& acc,const string& pass);
    std::unordered_map<std::string,std::string> get_accounts();
    std::unordered_map<std::string,FC_Connection*> get_onlineP();
    unordered_map<string,std::queue<FC_Message*>>& get_offlineM();
    void set_offlineM(const string& acc,FC_Message* msg);
    void set_friendsL(const string& acc,const string& str);
    std::unordered_map<std::string,vector<std::string>>& get_friends_list();

    void init_accounts();
    bool login_verify(const string& acc,const string& pass);
    bool  repeat_login(const string& acc,FC_Connection* con);
    bool update_nick(const string& acc,const string& nick);
    bool update_gender(const string& acc,const string& sex);

    //friends message
    bool update_mark(const QString& user_id,const QString& friend_id,const QString& mark);
    bool delete_friends(const QString& user_id,const QString& friend_id);


    static DbBroker* _broker;
private:
    FC_Thread_Pool* _thread_pool = nullptr;
    FC_Acceptor* _accrptor = nullptr;
    vector<FC_Connection*> _connected; //connected but not identify,这个主要是用于群聊
    std::unordered_map<std::string,FC_Connection*> _onlineP; //所有的在线好友信息connected and identified;
    std::unordered_map<std::string,std::string> _accounts;//用户账户信息列表
    unordered_map<string,std::queue<FC_Message*>> _offlineM;//离线消息队列
    std::unordered_map<std::string,vector<std::string>> _groupInfo;   //所有群ID和每个群ID中包含的各自群成员ID
    std::unordered_map<std::string,vector<std::string>> _firends_list; //用户　好友列表
};

#endif // FC_SERVER_H
