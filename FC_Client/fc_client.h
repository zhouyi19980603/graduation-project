#ifndef FC_CLIENT_H
#define FC_CLIENT_H

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <string>
#include <json/json.h>
#include "fc_status.h"
#include <unordered_map>

using boost::thread;
using std::string;
using boost::asio::io_service;

class FC_Connection;
class FC_Display;
class FC_Thread_Pool;
class FC_Profile;
class FC_Message;
class FC_Message_Handle;
class BuddyItem;

class FC_Client
{
public:
    FC_Client();
    ~FC_Client();

    //thread pool about
    io_service* get_logic_service(); //get io_service from thread_pool;

    //display about
    void add_msg_to_socket(FC_Message* msg);
    void add_msg_to_qml(FC_Message* msg);
    void add_msg_to_display(char* msg); //socket message to display
    void add_msg_to_display(std::vector<std::string> msg); //socket message to display
    void add_msg_to_socket(std::vector<std::string> msg); //display message to socket
    void add_group_msg_to_display(std::vector<std::string> msg);
    void add_history_to_display(FC_Message* msg);
    
    //profile about
    //set funcation
    void setUniqueUserName(std::string name);
    
    //get funcation
    std::string getUniqueUserName();

    void forward_message(FC_Message* msg);
    bool save_user_head(const std::string& acc,const string& heading);
    string save_image(const string& heading);
    string handle_user_head(const string& filepath); //所有需要发送图片都可以调用这个接口


    std::unordered_map<string,BuddyItem*>& get_item();
    void set_item(string& acc,BuddyItem* item);
    void set_status(FC_MessageStatus::Status sta);
    
private:
    FC_Connection* _connections = nullptr;//connect to server
    FC_Display* _display = nullptr;//user interface
    FC_Thread_Pool* _thread_pool = nullptr;
    FC_Profile* _profile = nullptr; //account information
    FC_Message_Handle* _message_handle; //handle message
    FC_MessageStatus* _status;
    std::string uniqueUserName; //现在用户模块单出来了 可以单独使用;
    std::unordered_map<string,BuddyItem*> _items; //存放所有的好友信息
};

#endif // FC_CLIENT_H

