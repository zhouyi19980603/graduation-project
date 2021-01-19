#include "fc_server.h"
#include "fc_acceptor.h"
#include "fc_thread_pool.h"
#include "fc_connection.h"
#include "fc_db_proxy.h"
#include "fc_message.h"
#include <iostream>
#include <QDebug>
#include <QSqlQuery>
#include <algorithm>
//==============================================
//  public function
//==============================================

DbBroker* FC_Server::_broker = new DbBroker ();
FC_Server::FC_Server(int thread_num,int port){
    //    _broker = new DbBroker(this);
    init_accounts();
    this->_thread_pool = new FC_Thread_Pool(thread_num);
    this->_accrptor = new FC_Acceptor(this,port);
    this->_thread_pool->init_thread_pool();
    
    
}
FC_Server::~FC_Server(){
    delete this->_thread_pool;
    delete this->_accrptor;
    delete this->_broker;
}

//thread_pool about
io_service* FC_Server::get_logic_service(){
    return this->_thread_pool->get_logic_service();
}
io_service* FC_Server::get_acceptor_service(){
    return this->_thread_pool->get_acceptor_service();
}

//connection about
FC_Connection* FC_Server::get_connection(){
    io_service* service = this->get_logic_service();
    return new FC_Connection(this,service);
}
void FC_Server::handle_connected(FC_Connection* connection)
{
    //handle connected socket
    qDebug()<<"handle connected socket";
    connection->read();
    this->_connected.push_back(connection);
}
void FC_Server::erase_connection(FC_Connection* connection)
{
    
    for(size_t i=0;i<_connected.size();++i){
        if(_connected[i]==connection){
            std::swap(_connected[i],_connected[_connected.size()-1]); //和最后一个交换位置
            _connected.erase(_connected.end()-1); // 擦除
            break;
        }
    }
    //这里还需要erase在线的好友列表
    for(auto it = this->_onlineP.begin();it !=this->_onlineP.end();)
    {
        if(it->second == connection)
            it = this->_onlineP.erase(it);
        else
            it++;
    }
    qDebug()<<"this->_onlineP.size:"<<this->_onlineP.size();
    
    delete connection; //delete之后调用析构函数会关掉_socket
}


//group chat,这个使用来群聊发送的
void FC_Server::forward_group_message(std::string id,string senderId, FC_Message *msg)
{
    std::vector<string> tmp ={"@12345","@24567","@13456"}; //差@23456
    this->_groupInfo.insert({{"@56789",tmp}});
     std::unordered_map<std::string,vector<std::string>>::iterator iter = this->_groupInfo.find(id);
     for(auto i = 0; i < iter->second.size() ;i++){
         if(iter->second.at(i)!= senderId)
            forward_message(iter->second.at(i),msg);
     }
}

//这个是端对端发送
void FC_Server:: forward_message(string id,FC_Message* msg){
    
    //在传送消息中进行离线处理
    for (auto i=_onlineP.begin();i!=_onlineP.end();++i) {
        if(i->first==id){
            FC_Message* tmp_msg = new FC_Message(*msg);
            i->second->write(tmp_msg);
        }
    }
}

//profile about
void FC_Server::add_identified(string s,FC_Connection* c){
    //    this->_identified[s] = c;
    this->_onlineP[s] = c;
}


void FC_Server::init_accounts()
{
    QSqlQuery qu = _broker->get_user_account();
    while (qu.next()) {
        QString account = qu.value(0).toString();
        QString password = qu.value(1).toString();
        set_accounts(account.toStdString(),password.toStdString());
    }
}

bool FC_Server::login_verify(const string &acc, const string &pass)
{
    //查看密码是否正确 同时查看这个帐号是否登录过
    if(_accounts[acc] == pass)
        return true;
    return false;
}

bool FC_Server::repeat_login(const std::string &acc, FC_Connection *con)
{
    if(_onlineP.count(acc))
        return false;
    else
        return true;
}



void FC_Server::set_accounts(const string &acc, const string &pass)
{
    _accounts[acc] = pass;
}

bool FC_Server::update_nick(const string &acc, const string &nick)
{
    DbBroker broker;
    return broker.update_nick(QString::fromStdString(acc),QString::fromStdString(nick));
}

bool FC_Server::update_gender(const string &acc, const string &sex)
{
    DbBroker broker;
    return broker.update_gender(QString::fromStdString(acc),QString::fromStdString(sex));
}

bool FC_Server::update_mark(const QString &user_id, const QString &friend_id, const QString &mark)
{
    DbBroker broker;
    return broker.update_mark(user_id,friend_id,mark);
}

bool FC_Server::delete_friends(const QString &user_id, const QString &friend_id)
{
    DbBroker broker;
    return broker.delete_friends(user_id,friend_id);
}

std::unordered_map<string, string> FC_Server::get_accounts()
{
    return this->_accounts;
}

std::unordered_map<std::string, FC_Connection *> FC_Server::get_onlineP()
{
    return this->_onlineP;
}

unordered_map<std::string, std::queue<FC_Message *> > &FC_Server::get_offlineM()
{
    return this->_offlineM;
}


void FC_Server::set_offlineM(const std::string &acc, FC_Message *msg)
{
    this->_offlineM[acc].push(msg);
}

void FC_Server::set_friendsL(const std::string &acc, const std::string &str)
{
    this->_firends_list[acc].push_back(str);
}

std::unordered_map<std::string, vector<std::string> > &FC_Server::get_friends_list()
{
    return _firends_list;
}

//==============================================
//  private function
//==============================================
