#include "fc_display.h"
#include "fc_client.h"
#include "fc_message_listmodel.h"
#include "fc_profile_handle.h"
#include "fc_message_handle.h"
#include "fc_profile.h"
#include "fc_buddymodel.h"
#include "fc_buddyitem.h"
#include "fc_buddyteam.h"
#include "fc_friends_handle.h"
#include "fc_buddy.h"
#include "fc_chat_listmodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QtQml>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <QDebug>
#include<iostream>
#include "./Moments/fc_moments_listmodel.h"
#include "./Moments/fc_moments_control.h"
#include "./Moments/fc_moments_like.h"
#include "./Moments/fc_comments_listmodel.h"

using boost::thread;


FC_Display::FC_Display(FC_Client* client,FC_Profile* profile)
    :_client(client),_profile(profile)
{
    _profilemsg = ProfileMsg::getInstance();
    _model = BuddyModel::getInstance();
    _handle = new FC_Message_Handle (client);
    _fhandle = new FC_Friends_Handle(client);
    //_profile = new FC_Profile (client);
    _buddy = Buddy::getInstance();
    _status = FC_MessageStatus::getInstance();
    this->_chat_listModel = new FC_Chat_ListModel();
    this->_list_model = new FC_Message_ListModel(_client,_chat_listModel,_profilemsg);

//    this->_moments_model = new FC_Moments_Model();
    this->_moments_model = FC_Moments_Model::getInstance();
    this->_control = new FC_Moments_Control (client);
    this->_msg = LikeMsg::getInstance();
    this->_comments_model = CommentsModel::getInstance();

}
FC_Display::~FC_Display(){
    qDebug() << "FC_Display::~Display\n";
    delete this->_engine;
    delete this->_app_ui;
    delete this->_profilemsg;
    delete this->_handle;
    delete this->_profile;
    delete this->_list_model;
    delete this->_fhandle;
}

void FC_Display::recv(QString s){
    this->_list_model->recv({".",".",".",s});
}

void FC_Display::recv_group_msg(std::vector<std::string> vs)
{
    std::cout <<"count打印测试"<<vs.at(2);
    this->_list_model->recv_group({QString::fromStdString(vs.at(0)),
                                   QString::fromStdString(vs.at(1)),    //消息接受这ID
                                   QString::fromStdString("."),
                                   QString::fromStdString(vs.at(2)),
                                  QString::fromStdString(vs.at(3))});
}
void FC_Display::recv(std::vector<std::string> vs){//display receive message
    std::cout <<"count打印测试"<<vs.at(2);
    this->_list_model->recv({QString::fromStdString(vs.at(0)),    //好友id
                             QString::fromStdString(vs.at(1)),    //消息接受这ID,也就是当前客户id
                             QString::fromStdString("."),
                             QString::fromStdString(vs.at(2)),   //消息
                             QString::fromStdString(vs.at(3))}); //type

    cout<<"_list_recv_model:"<<vs.at(0)<<"  :   "<<vs.at(1)<<endl;
}

void FC_Display::recv_history(FC_Message *msg)
{
    string tmpHistory = msg->body();
    //string tmpHistory = "{\"msgContent\":[\"@12345@23456反而完全个\",\"@12345@24567反而完全个\",\"@12345@24567发玩儿v\"]}";
    qDebug() <<"json 打印:"<< msg->body();
    Json::Value root;
    Json::Reader reader;


    if (reader.parse(tmpHistory, root))
    {
        //读取数组信息
        cout << "Here's history:" << endl;

        for (unsigned int i = 0; i < root["chats"].size(); i++)
        {
            string send_id,recv_id,time,content,type;
            send_id = root["chats"][i]["send_id"].asString();
            recv_id = root["chats"][i]["recv_id"].asString();
            time = root["chats"][i]["time"].asString();
            content = root["chats"][i]["msg_content"].asString();
            type = root["chats"][i]["msg_type"].asString();

            this->_list_model->handle_history({QString::fromStdString(send_id),
                                               QString::fromStdString(recv_id),    //消息接受这ID
                                               QString::fromStdString(time),
                                               QString::fromStdString(content),
                                               QString::fromStdString(type)});
//            //更改
//            string tmpContent = root["chats"][i].asString();
//            cout <<"元素打印"<< tmpContent<<endl;

//            const char* tmp = tmpContent.c_str();
//            char* w_account = new char[7];
//            memset(w_account,'\0',7);
//            char* m_account =new char[7];
//            memset(m_account,'\0',6);
//            memcpy(w_account,tmp,FC_ACC_LEN);  //第一个账号
//            memcpy(m_account,tmp+6,FC_ACC_LEN);//第二个账号
//            const char *content = tmp+12;  //消息内容

//            this->_list_model->handle_history({QString::fromStdString(w_account),
//                                               QString::fromStdString(m_account),    //消息接受这ID
//                                               QString::fromStdString("."),
//                                               QString::fromStdString(content),
//                                               QString::fromStdString("0")});  //文本消息

        }

        cout << "Reading Complete!" << endl;
    }
    else
    {
        cout << "parse error\n" << endl;
    }
}
void FC_Display::show(){
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    int argc=0;
    this->_app_ui = new QGuiApplication(argc,nullptr);
    this->_engine = new QQmlApplicationEngine;

    qmlRegisterType<BuddyItem>("buddy",1,0,"BuddyItem");
    qmlRegisterType<BuddyTeam>("buddy",1,0,"BuddyTeam");

    _engine->rootContext()->setContextProperty("teamModel",_model);
    _engine->rootContext()->setContextProperty("profile_handle",_profile);
    _engine->rootContext()->setContextProperty("profilemsg",_profilemsg);
    _engine->rootContext()->setContextProperty("buddy",_buddy);
    _engine->rootContext()->setContextProperty("friends_handle",_fhandle);
    _engine->rootContext()->setContextProperty("chat_listModel",this->_chat_listModel);
    _engine->rootContext()->setContextProperty("status_message",this->_status);
    this->_engine->rootContext()->setContextProperty("message_listModel",this->_list_model);
    this->_engine->rootContext()->setContextProperty("moments_model",this->_moments_model);
    this->_engine->rootContext()->setContextProperty("moments_control",this->_control);
    this->_engine->rootContext()->setContextProperty("msg",this->_msg);
    this->_engine->rootContext()->setContextProperty("comments_model",this->_comments_model);

    this->_engine->load(QUrl(QStringLiteral("qrc:/qml/Fc_MainWindow.qml")));
    this->_app_ui->exec();
}
