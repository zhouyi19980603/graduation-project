#include "fc_message_instance.h"
#include "fc_client.h"
#include <QDebug>
#include <vector>
#include <string>

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

    std::vector<std::string> msg;
    msg.push_back(content.at(0).toStdString());
    msg.push_back(content.at(1).toStdString());
    msg.push_back(content.at(2).toStdString());
    msg.push_back(content.at(3).toStdString());
    this->_client->add_msg_to_socket(msg);

}

void FC_Message_Instance::clearMsg()
{
    this->_data.clear();
}
