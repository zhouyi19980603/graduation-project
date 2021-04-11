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
#include "fc_moments_like.h"

using namespace boost::property_tree;

FC_Moments_Control::FC_Moments_Control(FC_Client *client, QObject *parent)
    :QObject(parent),_client(client)
{
//    _model = new FC_Moments_Model ();
    _model = FC_Moments_Model::getInstance();
    _profile = ProfileMsg::getInstance();
    _msg = LikeMsg::getInstance();//初始化
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
    //one.con_image = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/one.jpg";
    //这里会产生一个dyId
    //朋友圈id的产生，当前的时间
    time_t nowtime;
    struct tm* p;;
    time(&nowtime);
    p = localtime(&nowtime);

    char *times = new char;
    char *m_time = new char;
    sprintf(m_time,"%02d-%02d %02d:%02d",p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min);
    sprintf(times,"%02d:%02d:%02d:%02d:%02d",p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);

    one.time = m_time;//得到时间
    one.dyId = _profile->account()+":"+times;//得到当前id



    //写成json文件发送出去
    _model->add(one);

    string path = "/run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/one.jpg";



    ptree writeroot;
    writeroot.put("dyId",one.dyId.toStdString());
    writeroot.put("userId",_client->getUniqueUserName());
    writeroot.put("con_text","夜阑卧听风吹雨。");
    writeroot.put("con_image","image");
//    writeroot.put("con_image",_client->handle_user_head(path));
    writeroot.put("time",m_time);
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
    root["userNick"] = _profile->nickname().toStdString();
    QString newText = _msg->like_text()==""?_profile->nickname(): _msg->like_text()+","+_profile->nickname();
    _msg->setLike_text(newText);
    Json::FastWriter write;
    string content = write.write(root);
    FC_Message* message =  FC_Message_Handle::generate_message(FC_LIKE,content.c_str());
    //更新当前的点赞
    _client->add_msg_to_socket(message);
}

void FC_Moments_Control::request_dynamic_data()
{
    FC_Message* fc_message = new FC_Message;
    fc_message->set_message_type(FC_REQUEST_DY);
    fc_message->set_body_length(_profile->account().toStdString().size());
    fc_message->set_body(_profile->account().toStdString().c_str(),_profile->account().toStdString().size());
    _client->add_msg_to_socket(fc_message);
}

void FC_Moments_Control::handle_new_moments(const char* content)
{
    Json::Value root;
    Json::Reader reader;
    string id,text,image,dyId,time;
    if(!reader.parse(content,root))
    {
        std::cout <<"failed handle_new_moments" <<std::endl; //解析失败？？
    }else
    {
        dyId = root["dyId"].asString();
        id = root["userId"].asString();
        text = root["con_text"].asString();
        image = root["con_image"].asString();
        time = root["time"].asString();
    }
    dynamic nic;
    nic.dyId = QString::fromLocal8Bit(dyId.c_str());
    nic.userId = QString::fromLocal8Bit(id.c_str());
    nic.con_text = QString::fromLocal8Bit(text.c_str());

    //nic.con_image = QString::fromLocal8Bit(_client->save_image(image).c_str());
    nic.headpath = _client->get_item()[id]->heading();
    nic.nickname = _client->get_item()[id]->markname()=="" ? _client->get_item()[id]->nickname() : _client->get_item()[id]->markname();
    std::cout<<"FC_Moments_Control::handle_new_moments"<<std::endl;
    nic.time = QString::fromLocal8Bit(time.c_str());
    _model->add(nic);
}

void FC_Moments_Control::handle_like_message(const char *content)
{
    std::cout<<"handle_like_message: "<<content<<std::endl;
    //这里直接得到昵称，显示昵称在界面中
    QString newText = _msg->like_text()==""?content: _msg->like_text()+","+content;
    _msg->setLike_text(newText);
}

void FC_Moments_Control::handle_replay_dy(const char *content)
{
    std::cout<<"FC_Moments_Control::handle_replay_dy"<<content<<std::endl;
    _model->clear();//清空model
    Json::Reader reader;
    Json::Value root;
    //格式为"moments":[{},{},{}]
    if(reader.parse(content,root))
    {
        dynamic dy;
        //解析成功
        for(auto each: root["moments"])
        {
            dy.dyId = QString::fromLocal8Bit(each["post_id"].asString().c_str());
            dy.time = QString::fromLocal8Bit(each["time"].asString().c_str());
            dy.userId = QString::fromLocal8Bit(each["user_id"].asString().c_str());
            dy.con_text = QString::fromLocal8Bit(each["con_text"].asCString());
            dy.con_image = QString::fromLocal8Bit(each["con_image"].asCString());
            QString new_id = QString::fromLocal8Bit(each["user_id"].asString().c_str());
            dy.headpath = new_id == _profile->account() ? new_id:  _client->get_item()[each["user_id"].asString()]->heading();
            dy.nickname = new_id == _profile->account() ? _profile->nickname():_client->get_item()[each["user_id"].asString()]->markname()=="" ? _client->get_item()[each["user_id"].asString()]->nickname() : _client->get_item()[each["user_id"].asString()]->markname();

            QString like_text ;
            if(new_id == _profile->account())
            {
                //表明是自己的文章
                for(auto value: each["likes"])
                {
                    string user_id="";
                    user_id = value.asString();
                    like_text += user_id ==_profile->account().toStdString() ? _profile->nickname():_client->get_item()[user_id]->markname()=="" ? _client->get_item()[user_id]->nickname() : _client->get_item()[user_id]->markname();
                    like_text += "、";
                }
            }else
            {
                for(auto value: each["likes"])
                {

                    string user_id="";
                    user_id = value.asString();
                    //判断是不是自己的id
                    if(user_id == _profile->account().toStdString())
                    {
                        like_text += _profile->nickname();
                        like_text += "、";
                        continue;
                    }
                    //判断是否存在于自己的好友列表中，存在则显示
                    auto search = _client->get_item().find(user_id);
                    if(search != _client->get_item().end())
                    {
                        //表明找到了
                        like_text += new_id ==_profile->account() ? _profile->nickname():_client->get_item()[user_id]->markname()=="" ? _client->get_item()[user_id]->nickname() : _client->get_item()[user_id]->markname();
                        like_text += "、";
                    }
                }
            }
            dy.like_text = like_text;

            _model->add(dy);
        }
    }else
    {
        std::cout<<"解析出错"<<std::endl;
    }
}


