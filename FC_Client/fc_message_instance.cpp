#include "fc_message_instance.h"
#include "fc_client.h"
#include <QDebug>
#include <vector>
#include <string>
#include <json/json.h>
#include <fc_message.h>

//==============================================
//  public function
//==============================================

FC_Message_Instance::FC_Message_Instance(FC_Client* client):_client(client)
{
    int i = Qt::DisplayRole;
    this->_roles.insert(i++,"writer");
    this->_roles.insert(i++,"s_id");
    this->_roles.insert(i++,"time");
    this->_roles.insert(i++,"content");
    this->_roles.insert(i++,"type");            //消息类型,0:文本消息;1文件消息;2:图片消息
    this->_roles.insert(i++,"imagePathLeft");
    this->_roles.insert(i++,"imagePathRight"); //存一个头像值就行
    this->_roles.insert(i++,"msgOpacity"); //判断当前显示的位置
}



//override function
QVariant FC_Message_Instance::data(const int &index, int role ) const{ //index and role data
    return this->_data.at(index).at(role);
}

//函数返回模型中的项目总数
int FC_Message_Instance::rowCount() const{ //row count
    return this->_data.size();
}


QHash<int, QByteArray> FC_Message_Instance::roleNames() const{
    return this->_roles;
}


//display to socket
void  FC_Message_Instance::add(QVector<QString> content){//display to socket
    _data.push_back(content);
}

void FC_Message_Instance::recv(QVector<QString> content){//socket to display
    _data.push_back(content);
}

void FC_Message_Instance::add_msg_to_socket(QVector<QString> content)
{
    Json::Value root;
    //生成id
    time_t nowtime;
    struct tm* p;;
    time(&nowtime);
    p = localtime(&nowtime);

    char *times = new char;
    char *m_time = new char;
    sprintf(m_time,"%02d-%02d %02d:%02d",p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min);
    sprintf(times,"%02d:%02d:%02d:%02d:%02d",p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
    root["id"] = content.at(0).toStdString()+":"+times;
    root["send_id"] = content.at(0).toStdString();
    root["recv_id"] = content.at(1).toStdString();
    root["msg_type"] = content.at(4).toStdString();
    root["msg_content"] = content.at(3).toStdString();
    root["time"] = m_time;
    Json::FastWriter write;
    string str =  write.write(root);
    FC_Message *msg = new FC_Message();
    msg->set_message_type(FC_TEXT_MEG);
    msg->set_body_length(str.size());
    msg->set_body(str.c_str(),str.size());
    _client->add_msg_to_socket(msg);


    //this->_client->forward_message()
//    std::vector<std::string> msg;
//    msg.push_back(content.at(0).toStdString());
//    msg.push_back(content.at(1).toStdString());
//    msg.push_back(content.at(2).toStdString());
//    msg.push_back(content.at(3).toStdString());
//    this->_client->add_msg_to_socket(msg);
    //this->_client->forward_message()

}

void FC_Message_Instance::clearMsg()
{
    this->_data.clear();
}
