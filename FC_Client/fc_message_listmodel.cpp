#include "fc_message_listmodel.h"
#include "fc_message_instance.h"
#include "fc_client.h"
#include "fc_buddyitem.h"
#include "fc_chat_listmodel.h"
#include "fc_base64encrypt.h"
#include "fc_message.h"
#include "fc_profile.h"
#include <QDebug>
#include <fstream>
#include <filesystem>
#include <string>
#include <zlib.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>

namespace fs =std::filesystem ;
using namespace std;

//==============================================
//  public function
//==============================================


FC_Message_ListModel::FC_Message_ListModel(FC_Client*client,FC_Chat_ListModel* chat_list_model,ProfileMsg* profile, QObject* parent)
    :QAbstractListModel(parent),_client(client),_chat_listModel(chat_list_model),_profile(profile)
{

    _instace = new FC_Message_Instance(_client);
//    QVector<QVector<QString>> tmp;
//    _all_mess.insert("@12345",tmp);
//    _all_mess.insert("@24567",tmp);
//    _all_mess.insert("@23456",tmp);
//    _all_mess.insert("@13456",tmp);

//    //群ID:
//    _all_mess.insert("@56789",tmp);

}
FC_Message_ListModel::~FC_Message_ListModel(){
    delete this->_instace;
}

MsgVector::iterator FC_Message_ListModel::handle_own_msg(QVector<QString> content)
{
    MsgVector::iterator iter =this->_all_mess.find(content.at(1));  //检索key
    if(iter == this->_all_mess.end())
    {
        QVector<QVector<QString>> tmp;
        tmp.push_back(content);
        _all_mess.insert(content.at(1),tmp);
    }else
        iter.value().push_back(content);

    return iter;
}

void FC_Message_ListModel::handle_history(QVector<QString> content)
{
    if(content.at(0) == this->_profile->account()){
        this->_is_history=false;
        add(content);
    }else {
        this->_is_history=false;
        recv(content);
    }
}

MsgVector::iterator FC_Message_ListModel::handle_recv_msg(QVector<QString> content)
{
    qDebug()<<"key date:"<<content.at(0)+content.at(1);
    MsgVector::iterator iter =this->_all_mess.find(content.at(0));  //检索key
    if(iter == this->_all_mess.end())
    {
        QVector<QVector<QString>> tmp;
        tmp.push_back(content);
        _all_mess.insert(content.at(0),tmp);
    }else
        iter.value().push_back(content);

    return iter;
}


void FC_Message_ListModel::add_msg_to_socket(QVector<QString> content)
{
    this->_instace->add_msg_to_socket(content);
}

QString FC_Message_ListModel::get_head_path(QString id)
{

    fs::path p = fs::current_path(); //目的是为了得到相对路径
    std::string tmpAccount = id.toStdString();
    std::string path = "file://"+p.string()+"/assert/"+tmpAccount+".jpg";
    QString headpath = QString::fromLocal8Bit(path.c_str());
    return headpath;
}

//override function
QVariant FC_Message_ListModel::data(const QModelIndex &index, int role ) const{ //index and role data
    return this->_instace->data(index.row(),role);
}
//函数返回模型中的项目总数
int FC_Message_ListModel::rowCount(const QModelIndex &) const{//row count
    return this->_instace->rowCount();
}

QHash<int, QByteArray> FC_Message_ListModel::roleNames() const{
    return this->_instace->roleNames();
}


//transfer function
void FC_Message_ListModel::add(QVector<QString> content){// display to socket
    if((content.at(4).toInt()) == 0 && (this->_is_history ==true)) //text content
        add_msg_to_socket(content); //传送给了服务端
    else if(content.at(4).toInt() == 1) //file content  ,2是图片消息
    {
        send_file(content.at(1),content.at(5));
        content.removeLast();
    }

//    time_t nowtime;
//    struct tm* p;;
//    time(&nowtime);
//    p = localtime(&nowtime);

//    char *m_time = new char;
//    sprintf(m_time,"%02d-%02d %02d:%02d",p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min);
//    content[2] = QString::fromLocal8Bit(m_time);//时间
    QString tmpPathLeft= get_head_path(content.at(1));
    QString tmpPathRight = get_head_path(content.at(0));

    content.push_back(tmpPathLeft);         //添加对应头像路径
    content.push_back(tmpPathRight);
    content.push_back("0"); //设置可见还是不可见
    handle_own_msg(content);
    //这里传入的是账户 内容 头像 名字 时间
    QString name =  _client->get_item()[content.at(1).toStdString()]->markname() =="" ? _client->get_item()[content.at(1).toStdString()]->nickname() : _client->get_item()[content.at(1).toStdString()]->markname();
    this->_chat_listModel->add({content.at(1),content.at(3),content.at(5),name,content.at(2)});

    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    //消息直接在UI上打印
    this->_instace->add(content);
    endInsertRows();
    emit recv_mess();
    this->_is_history=true;
}
void FC_Message_ListModel::recv(QVector<QString> content){// socket to display
    //添加对应头像路径
    //这里也可以直接调用 好友列表的接口，不需要自己重新获取头像路径
    QString tmpPathLeft= get_head_path(content.at(0));
    QString tmpPathRight = get_head_path(content.at(1));

    content.push_back(tmpPathLeft);
    content.push_back(tmpPathRight);
    content.push_back("1");
    handle_recv_msg(content);
    QString name =  _client->get_item()[content.at(0).toStdString()]->markname() =="" ? _client->get_item()[content.at(0).toStdString()]->nickname() : _client->get_item()[content.at(0).toStdString()]->markname();
    this->_chat_listModel->add({content.at(0),content.at(3),content.at(6),name,content.at(2)});
//    this->_chat_listModel->set_last_msg({content.at(0),content.at(3),content.at(6),name,content.at(2)});
    //检测是否为当前聊天信息
    if(content.at(0) !=this->currentChatId()){
        return;
    }
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    //消息直接在UI上打印
    this->_instace->recv(content);
    endInsertRows();
    emit recv_mess();
    this->_is_history=true;
}

void FC_Message_ListModel::recv_group(QVector<QString> content)
{
    handle_own_msg(content);
//    this->_chat_listModel->set_last_msg({content.at(0),content.at(3),content.at(5)});
    QString tmpPathLeft= get_head_path(content.at(0));
    QString tmpPathRight = get_head_path(_profile->account());
    content.push_back(tmpPathLeft);
    content.push_back(tmpPathRight);
    content.push_back("1");
    handle_recv_msg(content);
//    this->_chat_listModel->set_last_msg({content.at(0),content.at(3),content.at(5)});
    //检测是否为当前聊天信息

    if(content.at(1) !=this->currentChatId()){
        return;
    }
    set_msgOpacity(true);
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    //消息直接在UI上打印
    this->_instace->recv(content);
    endInsertRows();
    emit recv_mess();
}

void FC_Message_ListModel::loadMsg(QString key)
{
    qDebug()<<"key data:"<<key;
    this->_instace->clearMsg();  //清空信息

    qDebug()<<"load key data: "<<key;
    MsgVector:: iterator iter =this->_all_mess.find(key);
    if(iter != _all_mess.end())
    {
        for(int i = 0; i < iter->length();i++){
            //消息直接在UI上打印
            if(iter.value().at(i).at(0) == key){
                set_msgOpacity(true);
                //添加对应头像路径
                beginInsertRows(QModelIndex(),rowCount(),rowCount());
                this->_instace->recv(iter.value().at(i));
                endInsertRows();
                emit recv_mess();
            }else {
                set_msgOpacity(false);
                beginInsertRows(QModelIndex(),rowCount(),rowCount());
                this->_instace->add(iter.value().at(i));
                endInsertRows();
                emit recv_mess();
            }
        }
    }


}

QString FC_Message_ListModel::currentChatId() const
{
    return this->_currentChatId;
}

void FC_Message_ListModel::set_currentChatId(QString id)
{
    this->_currentChatId = id;
    loadMsg(id);
}


bool FC_Message_ListModel::msgOpacity() const
{
    return this->_msgOpacity;
}

bool FC_Message_ListModel::set_msgOpacity(bool tmp)
{
    return this->_msgOpacity = tmp;
}

void FC_Message_ListModel::insertMsgVectorKey(const QString &name)
{
    QVector<QVector<QString>> tmp;
    _all_mess.insert(name,tmp);
}

void FC_Message_ListModel::send_file(const QString &acc, const QString &filepath)
{
    string filename = fs::path(filepath.toStdString()).filename();
    ifstream in(filepath.toStdString(),std::ios::binary);
    if(!in.is_open())
        qDebug()<<"open failed";

    stringstream buffer;
    buffer<<in.rdbuf();

    string contents(buffer.str());

    uLong  srcLength = contents.size();
    uLong  destLength = compressBound(srcLength+1); //预期的压缩大小
    char *dest = nullptr;
    dest = new char[destLength];

    cout<<"destLength:"<<destLength<<endl;

    //压缩

    if(compress((Bytef *)dest, &destLength, (Bytef *)contents.c_str(), srcLength) != Z_OK)
     {
       printf("compress failed!\n");
       exit(0);
     }

    //加密
    Base64Encrypt encrypt(dest,destLength);

    string result = encrypt.GetString();
    Json::Value root;
    Json::FastWriter write;
    root["name"]=filename; //写出来位置是颠倒的
    root["content"] = result;//传过去的值，是减压后的值
    root["length"] = contents.size();

    string content = write.write(root);


    FC_Message* msg = new FC_Message ();
    msg->set_message_type(FC_FILE_MEG);
    msg->set_body_length(content.size()+FC_ACC_LEN*2);
    msg->set_self_identify(_client->getUniqueUserName().c_str());
    msg->set_friend_identify(acc.toStdString().c_str());
    msg->set_core_body(content.c_str(),content.size());

    _client->add_msg_to_socket(msg);

    //数据从200K变为了15.1k
}

void FC_Message_ListModel::open_file(const QString &filename)
{
    //这里所得到的文件名都是当前可执行路径下的 所以可以直接调用fork进程 用exec函数去替换
    char* arglist[3]; //数组中的每一个值都是一个指针
    arglist[0] = "wps";

    char* file =filename.toLocal8Bit().data();
    arglist[1] = file;
    arglist[2] = 0;

    pid_t pid;
    pid = fork(); //进程

    if(pid == 0) //子进程去处理这个事情
    {
        execvp("wps",arglist);
    }else if(pid <0)
    {
        exit(0);
    }
}





