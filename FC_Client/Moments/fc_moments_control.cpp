#include "fc_moments_control.h"
#include "fc_message.h"
#include "json/json.h"
#include "fc_client.h"
#include "fc_buddyitem.h"
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "fc_profile.h"
#include "fc_message_handle.h"

using namespace boost::property_tree;

FC_Moments_Control::FC_Moments_Control(FC_Client *client, QObject *parent)
    :QObject(parent),_client(client)
{
//    _model = new FC_Moments_Model ();
    _model = FC_Moments_Model::getInstance();
    _profile = ProfileMsg::getInstance();
}

FC_Moments_Control::~FC_Moments_Control()
{

}

void FC_Moments_Control::publish_dynamic()
{
    dynamic one;
    one.headpath = _profile->heading(); //个人信息的头像
    one.nickname = _profile->nickname(); //个人信息的网名
    one.con_text = "夜阑卧听风吹雨。";
    one.con_image = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/one.jpg";
    //这里会产生一个dyId
    //朋友圈id的产生，当前的时间
    time_t nowtime;
    struct tm* p;;
    time(&nowtime);
    p = localtime(&nowtime);

    //char *times = new char;
    //sprintf(times,"%02d:%02d:%02d:%02d:%02d",p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
   // one.dyId = _profile->account()+":"+times;//得到当前id


    //写成json文件发送出去
    _model->add(one);

    string path = "/run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/one.jpg";



    ptree writeroot;
    writeroot.put("dyId",one.dyId.toStdString());
    writeroot.put("userId",_client->getUniqueUserName());
    writeroot.put("con_text","夜阑卧听风吹雨。");
    writeroot.put("con_image",_client->handle_user_head(path));
    std::stringstream ss;
    boost::property_tree::write_json(ss,writeroot);

    string content = ss.str();

//    Json::Value root;
//    Json::FastWriter write;

//    root["userId"] = _client->getUniqueUserName();
//    root["con_text"] = "夜阑卧听风吹雨。";
////    string path = "/run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/one.jpg";
//    string path="/run/media/root/linux_data/FC_IM/build-FC_Client_ran-Desktop_Qt_5_14_0_GCC_64bit-Debug/assert/323813.jpg";

//    root["con_image"] = _client->handle_user_head(path);

////    std::cout<<_client->handle_user_head(path).size()<<std::endl;


//    string content = write.write(root);

    FC_Message* fc_message = new FC_Message;
    fc_message->set_message_type(FC_NEW_MOMENTS);
    fc_message->set_body_length(content.size());
    fc_message->set_body(content.c_str(),content.size());

    _client->add_msg_to_socket(fc_message);

}
//点赞发送给服务端
void FC_Moments_Control::like(QString id)
{
    Json::Value root;
    root["dyId"] = id.toStdString();
    root["userId"] = _profile->account().toStdString();
    Json::FastWriter write;
    string content = write.write(root);
    FC_Message* message =  FC_Message_Handle::generate_message(FC_LIKE,content.c_str());
    //更新当前的点赞
    //_client->add_msg_to_socket(message);
}

void FC_Moments_Control::handle_new_moments(const char* content)
{
    Json::Value root;
    Json::Reader reader;
    string id,text,image,dyId;
    if(!reader.parse(content,root))
    {
        std::cout <<"failed handle_new_moments" <<std::endl; //解析失败？？
    }else
    {
        dyId = root["dyId"].asString();
        id = root["userId"].asString();
        text = root["con_text"].asString();
        image = root["con_image"].asString();
    }
    dynamic nic;
    nic.dyId = QString::fromLocal8Bit(dyId.c_str());
    nic.userId = QString::fromLocal8Bit(id.c_str());
    nic.con_text = QString::fromLocal8Bit(text.c_str());

    nic.con_image = QString::fromLocal8Bit(_client->save_image(image).c_str());
    nic.headpath = _client->get_item()[id]->heading();
    nic.nickname = _client->get_item()[id]->markname()=="" ? _client->get_item()[id]->nickname() : _client->get_item()[id]->markname();
    std::cout<<"FC_Moments_Control::handle_new_moments"<<std::endl;
    _model->add(nic);
}


