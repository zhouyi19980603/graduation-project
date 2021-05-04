#include "fc_message_handle.h"
#include <QDebug>
#include <QQuickItem>
#include <QQuickView>
#include <memory>
#include <string>
#include <json/json.h>
#include <filesystem>
#include "fc_friends_handle.h"
#include "./Moments/fc_moments_control.h"
#include "fc_buddy.h"
#include "fc_profile_handle.h"
#include "fc_base64decrypt.h"
#include <iostream>
#include <zlib.h>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;

FC_Message_Handle::FC_Message_Handle(FC_Client *client)
    :_client(client)
{
    _friends_handle = new FC_Friends_Handle(client);
    _profile = new FC_Profile (client);
    _moment_handle = new FC_Moments_Control (client);
}

FC_Message_Handle::~FC_Message_Handle()
{
    delete _friends_handle;
    delete _profile;
}
void FC_Message_Handle::handle_header(FC_Message *message){
    message->set_body_length(message->body_length());
}

void FC_Message_Handle::handle_body(FC_Message* message){
    unsigned type = message->mess_type();
    //according message type handle message
    if(type&FC_PROFILE){
        switch (type) {
        case FC_SIGN_IN_R:
            cout<<"处理登录结果"<<endl;
            _profile->handle_login(message->body());
            break;
        case FC_SELF_MES:
            //            _client->json_data_parser_self(message->body());
            _profile->parser_json(message->body());
            break;
        case FC_UPDATE_NICK:
            _profile->update_nick(message->body());
            //            _client->update_nick(message->body());
            break;
        case FC_UPDATE_SEX:
            //            _client->update_gender(message->body());
            _profile->update_gender(message->body());
            break;

        case FC_UPDATE_HEAD:
            _profile->update_heading(message->body());
            break;
        case FC_REGISTER_R:
            cout<<"注册帐号： "<<message->body()<<endl;
            _profile->handle_reguster(message->body());
            break;
        default:
            cout<<"没有这样的类型"<<endl;
            break;
        }
    }else if(type & FC_FRIENDS){
        switch (type) {
        case FC_FRIENDS_SEARCH_R:
            std::cout<<"come on result"<<std::endl;
            _friends_handle->displaytoQML(message);
            //show search result
            break;
        case FC_FRIENDS_ADD:
            //QML中显示
            _friends_handle->displaytoQML(message);
            break;
        case FC_FRIENDS_ADD_R:
        {
            _friends_handle->refresh_friends_list(message->body());
            break;
        }
        case FC_FRIENDS_MESSAGE:
        {
            _friends_handle->parser_friends_json(message->body());
            cout<<"_friends_handle->get_item().size()"<<_friends_handle->get_item().size()<<endl;
            break;
        }
        case FC_FRIENDS_TEST:
            std::cout<<"测试数据"<<std::endl;
            break;
        case FC_FRIENDS_REMARK:
            std::cout<<"修改好友备注"<<std::endl;
            //            _friends_handle->update_remark(message->body());
            break;
        case FC_DELETE_FRIENDS:
            //删除好友
            _friends_handle->delete_friend(message->body());
            break;
        default:
            cout<<"好友没有这样的类型"<<endl;
            break;
        }
    }else if(type & FC_MESSAGES ){
        switch (type) {
        case FC_TEXT_MEG:
            handle_text_msg(message);
            break;
        case FC_GROUP_TEXT_MEG:
            handle_group_text_msg(message);
            break;
        case FC_TEXT_MEG_HISTORY:
            handle_history(message);
            break;
        case FC_FILE_MEG:
            handle_file_text_msg(message);
            break;
        default:
            cout<<"没有这个类型"<<endl;
        }

    }else if(type & FC_MOMENTS){
        switch (type) {
        case FC_LIKE:
            _moment_handle->handle_like_message(message->body());
            break;
        case FC_REPLY_COMMENTS:
            _moment_handle->handle_replay_comments(message->body());
            break;
        case FC_NEW_MOMENTS:
            _moment_handle->handle_new_moments(message->body());
            break;
        case FC_REPLY_DY:
            _moment_handle->handle_replay_dy(message->body());
            break;
        case FC_COMMENTS_REPLY1:
            //单纯的回复
            cout<<"FC_COMMENTS_REPLY1"<<endl;
            _moment_handle->handle_comment_reply(message->body(),1);
            break;
        case FC_COMMENTS_REPLY2:
            cout<<"FC_COMMENTS_REPLY2"<<endl;
            _moment_handle->handle_comment_reply(message->body(),2);
            //回复的回复，处理格式不同
            break;
        default:
            cout<<"朋友圈没有这样的类型"<<endl;
            break;
        }
    }
    else{
        qDebug() << "unknow message type:" << message->mess_type();
    }
}


void FC_Message_Handle::handle_text_msg(FC_Message* msg){

    //处理文本消息
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(msg->body(),root))
    {
        std::cout <<"FC_Message_Handle::handle_text_msg(FC_Message* msg)" <<std::endl;
        exit(0);
    }
    string send_id,recv_id,cont,type;
    send_id = root["send_id"].asString();
    recv_id = root["recv_id"].asString();
    cont = root["msg_content"].asString();
    type = root["msg_type"].asString();

    std::vector<std::string> vs(4);
    vs.at(0) = send_id;
    vs.at(1) = recv_id;
    vs.at(2) = cont;
    vs.at(3) = type;
    this->_client->add_msg_to_display(vs);
}

void FC_Message_Handle::
handle_group_text_msg(FC_Message *msg)
{
    char* w_account = new char[7];
    memset(w_account,'\0',7);
    char* m_account =new char[7];
    memset(m_account,'\0',7);
    memcpy(w_account,msg->header()+sizeof (unsigned)*2,FC_ACC_LEN);
    memcpy(m_account,msg->header()+14,FC_ACC_LEN);
    char *content = msg->body()+12;  //消息内容
    std::vector<std::string> vs(4);
    qDebug()<<"客户端群消息:"<< content;
    vs.at(0)=w_account;   //消息发送者id
    vs.at(1)=m_account;   //消息接收者id
    vs.at(2)=content;     //消息内容
    vs.at(3) = "0";       //消息type
    this->_client->add_group_msg_to_display(vs);
    free(w_account);
    free(m_account);
}

void FC_Message_Handle::handle_history(FC_Message *message)
{
    this->_client->add_history_to_display(message);
//    qDebug() <<"json message 打印:"<<message->body();
}

void FC_Message_Handle::handle_file_text_msg(FC_Message *msg)
{
    //save current path
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(msg->get_core_body(), root)){
        std::cout <<"failed" <<std::endl;
        exit(0);
    }
    string name = root["name"].asString();
    int length = root["length"].asInt();
    string content1 = root["content"].asString();

    Base64Decrypt decrypt(content1.c_str(),content1.size()); //解码
    uLong srcL = decrypt.GetSize();
    char* destV = new char[length];
    uLong destL;
    string value = decrypt.GetString();
    int error = uncompress((Bytef *)destV, &destL, (Bytef *)value.c_str(), srcL);
    if(error == Z_MEM_ERROR)
    {
        printf("compress failed! memoey error\n");
        exit(0);
    }else if(error == Z_DATA_ERROR)
    {
        printf("compress failed! data error\n");
        exit(0);
    }else if(error == Z_BUF_ERROR)
    {
        printf("compress failed! buf error\n");
        exit(0);
    }

    std::ofstream fout(name, std::ios::binary);
    if(!fout)
    {
        std::cout<<"open failed";
        exit(0);
    }
    fout.write(destV, destL);
    fout.close();
    delete []destV;

    cout<<"msg->get_self_identify():"<<msg->get_self_identify()<<endl;
    cout<<"msg->get_friends_identify():"<<msg->get_friends_identify()<<endl;
    std::vector<std::string> vs(4);
    vs.at(0) = msg->get_self_identify(); //消息发送者id
    vs.at(1) = msg->get_friends_identify(); //消息接收者id
    vs.at(2) = name;
    vs.at(3) = "1";
    this->_client->add_msg_to_display(vs);
}
const char* FC_Message_Handle::text_body(const char* content){
    int n = strlen(content)+1;
    char * ret = (char*) malloc(n+1);
    memset(ret,'\0',n);
    memcpy(ret,content,strlen(content));
    return ret;
}

FC_Message* FC_Message_Handle::generate_message(unsigned type,const char* content){
    //use the copy of the content
    //sizeof (a) = strlen(a)+1;
    FC_Message* message = new FC_Message;//delete in on_write()
    //message->set_message_type(type);
    unsigned msg_size = strlen(content)+1;
    message->set_header(type,msg_size);
    message->set_body(content,msg_size);
    return message;
}

