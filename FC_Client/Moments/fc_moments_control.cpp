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
#include "fc_comments_listmodel.h"

using namespace boost::property_tree;

FC_Moments_Control::FC_Moments_Control(FC_Client *client, QObject *parent)
    :QObject(parent),_client(client)
{
    //    _model = new FC_Moments_Model ();
    _model = FC_Moments_Model::getInstance();
    _profile = ProfileMsg::getInstance();
    _msg = LikeMsg::getInstance();//初始化
    _comment_model = CommentsModel::getInstance();
}

int flag = 1;
FC_Moments_Control::~FC_Moments_Control()
{

}

std::string FC_Moments_Control::getCurrentTime()
{
    time_t nowtime;
    struct tm* p;;
    time(&nowtime);
    p = localtime(&nowtime);

    char *times = new char;
    char *m_time = new char;
    sprintf(m_time,"%02d-%02d %02d:%02d",p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min);
    return  m_time;
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
    //设置当前这条为被点赞过
    //QString newText = _msg->like_text()==""?_profile->nickname(): _msg->like_text()+","+_profile->nickname();
    //_msg->setLike_text(newText);
//    QString newText = _msg->like_text()==""?_profile->nickname(): _msg->like_text()+"、"+_profile->nickname();

    QString newText = _profile->nickname();
    _model->update_model(id,newText);
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

void FC_Moments_Control::parsing()
{
    _comment_model->clear();
    //从json文件中读取，并获得是添加在那个项中
    Json::Value root;
    Json::Reader reader;
    std::ifstream is;

    is.open("./config/comments.json",std::ios::binary);
    if(reader.parse(is,root,false))
    {
        //解析到json文件,获得评论表
        Json::Value ids = root["ids"];
        for(int i=0;i<ids.size();i++)
        {
            //评论信息要通过判断user_id确定是不是好友来确定是否显示评论信息，不是好友则不会显示
            Comment com;
            //从"comments"中获取对应的ids
            std::string id = ids[i].asString();
            Json::Value item = root["comments"][id]; //得到对应的评论数据
            string user_id = item["user_id"].asString();//评论消息的user_id
            string puser_id = item["puser_id"].asString();//被评论的id
            //暂时所有都显示
            //            auto search = _client->get_item().find(user_id);
            //            if(search == _client->get_item().end() && user_id != _profile->account().toStdString())
            //                continue; //表明不是好友就不进行下面操作
            //            if(puser_id != "" && _client->get_item().find(user_id) ==  _client->get_item().end() && puser_id != _profile->account().toStdString())
            //                continue;
            com.id = QString::fromLocal8Bit(item["id"].asCString());
            com.content = QString::fromLocal8Bit(item["content"].asCString());
            com.parent_id = QString::fromLocal8Bit(item["parent_id"].asCString());
            //name需要重组
            //            com.name =QString::fromLocal8Bit(item["user_id"].asCString());
            if(com.parent_id == "")
            {
                if(user_id == _profile->account().toStdString())
                {
                    com.name = _profile->nickname();
                }else
                    com.name = _client->get_item()[user_id]->markname()==""?_client->get_item()[user_id]->nickname():_client->get_item()[user_id]->markname();
            }else
            {
                if(user_id == _profile->account().toStdString())
                {
                    com.name = _profile->nickname() + "回复";
                }else
                {
                    com.name = _client->get_item()[user_id]->markname()==""?_client->get_item()[user_id]->nickname():_client->get_item()[user_id]->markname() + "回复";

                }
                if(puser_id == _profile->account().toStdString())
                {
                    com.name += _profile->nickname();
                }else
                    com.name += _client->get_item()[puser_id]->markname()==""?_client->get_item()[puser_id]->nickname():_client->get_item()[puser_id]->markname();

            }
            com.user_id = QString::fromLocal8Bit(item["user_id"].asCString());
            com.puser_id = QString::fromLocal8Bit(item["puser_id"].asCString());
            com.time = QString::fromLocal8Bit(item["time"].asCString());
            com.post_id = QString::fromLocal8Bit(item["post_id"].asCString());
            if(item["parent_id"] == "")
            {
                //表明这是一级评论
                _comment_model->add(com,_comment_model->rowCount());
            }else
            {
                //表明父_id有值，这是一个回复,找到父_id所在的位置
                int index = _comment_model->getIndex(item["parent_id"].asString());
                _comment_model->add(com,index);
                std::cout<<"index: :"<<index<<std::endl;
            }
        }
    }else
    {
        std::cout<<"解析失败"<<std::endl;
        exit(0);
    }
    std::cout<<"_comment_model->rowCount()"<<_comment_model->rowCount()<<std::endl;

}
//QML端传来post_id,向服务端请求
void FC_Moments_Control::request_post_comments_data(const QString &post_id)
{
    FC_Message* fc_message = new FC_Message;
    fc_message->set_message_type(FC_REQUEST_COMMENTS);
    fc_message->set_body_length(post_id.toStdString().size());
    fc_message->set_body(post_id.toStdString().c_str(),post_id.toStdString().size());
    _client->add_msg_to_socket(fc_message);
}
//里面post_id,content,user_id,parent_id从QML界面传来,和下面合并为一起，处理的类型不同即可
void FC_Moments_Control::send_reply_comment(QVector<QString> con)
{
    //已经与下一个函数合并
}
//0为类型，表明是回复好友的，还是真实评论,1为post_id,2为content，3为被回复的user_id,4parent_id
//里面有post_id,content从QML界面传来
void FC_Moments_Control::send_comment(QVector<QString> con)
{

    for(auto each : con)
        std::cout<< each.toStdString() << std::endl;

    unsigned msg_type;
    Comment cm;
    if(con.at(0) == "2")
    {
        string puser_id = con.at(3).toStdString();
        cm.puser_id = puser_id.c_str();
        cm.parent_id = con.at(4);
        cm.name = _profile->nickname() + " 回复 ";
        cm.name += _client->get_item()[puser_id]->markname() == ""? _client->get_item()[puser_id]->nickname() : _client->get_item()[puser_id]->markname();
        std::cout<< "cm.name"<<cm.name.toStdString() << std::endl;
        msg_type = FC_COMMENTS_REPLY2;
    }else
    {
        cm.name = _profile->nickname() + " 回复 "; //这里为1
        cm.puser_id = "";
        cm.parent_id = "";
        msg_type = FC_COMMENTS_REPLY1;
    }
    cm.time = getCurrentTime().c_str();
    cm.content = con.at(2);
    cm.post_id = con.at(1);
    cm.user_id = _profile->account();
    cm.id = _profile->account() + getCurrentTime().c_str();

    _comment_model->add(cm,_comment_model->rowCount());

    //写了发送到服务端中

    Json::Value root;
    root["id"] = cm.id.toStdString();
    root["name"] = "";//name不用发送过去可以重新组装
    root["content"] = cm.content.toStdString();
    root["post_id"] = cm.post_id.toStdString();
    root["user_id"] = cm.user_id.toStdString();
    root["parent_id"] = cm.parent_id.toStdString();
    root["time"] = cm.time.toStdString();
    root["puser_id"] = cm.puser_id.toStdString();

    Json::FastWriter write;
    string content = write.write(root);

    FC_Message* message =  FC_Message_Handle::generate_message(msg_type,content.c_str());
//    _client->add_msg_to_socket(message);
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
//    std::cout<<"handle_like_message: "<<content<<std::endl;
//    //这里直接得到昵称，显示昵称在界面中
//    QString newText = _msg->like_text()==""?content: _msg->like_text()+","+content;
//    _msg->setLike_text(newText);
      //得到对应的post_id,找到post_id对内容进行修改
    Json::Value root;
    Json::Reader reader;
    string dyId,userId,userNickname;
    if(!reader.parse(content,root))
    {
        exit(0);
    }else
    {
        dyId = root["dyId"].asString();
        userId = root["userId"].asString(); //点赞的user_id
        //userNickname = root["userNick"].asString(); //点赞的nickname
    }
    //判断这个user_id是不是我的好友，是就进行操作
    if(_client->get_item().find(userId) != _client->get_item().end())
    {
        //是好友
        QString content = _client->get_item()[userId]->markname() == "" ? _client->get_item()[userId]->nickname() : _client->get_item()[userId]->markname();
        _model->update_model(dyId.c_str(),content);
    }
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
                    if(user_id == _profile->account().toStdString())
                        dy.is_like = true;
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
                        dy.is_like = true; //表明自己点过赞
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
                    //没有找到则不显示
                }
            }
            dy.like_text = like_text;

            _model->add(dy);
        }
    }else
    {
        std::cout<<"解析出错"<<std::endl;
        exit(0);
    }
}

void FC_Moments_Control::handle_replay_comments(const char *content)
{
    _comment_model->clear();
    //从json文件中读取，并获得是添加在那个项中
    Json::Value root;
    Json::Reader reader;

    if(reader.parse(content,root))
    {
        //解析到json文件,获得评论表
        Json::Value ids = root["ids"];
        for(int i=0;i<ids.size();i++)
        {
            //评论信息要通过判断user_id确定是不是好友来确定是否显示评论信息，不是好友则不会显示
            Comment com;
            //从"comments"中获取对应的ids
            std::string id = ids[i].asString();
            Json::Value item = root["comments"][id]; //得到对应的评论数据
            string user_id = item["user_id"].asString();//评论消息的user_id
            string puser_id = item["puser_id"].asString();//被评论的id


            //暂时所有都显示
            //            auto search = _client->get_item().find(user_id);
            //            if(search == _client->get_item().end() && user_id != _profile->account().toStdString())
            //                continue; //表明不是好友就不进行下面操作
            //            if(puser_id != "" && _client->get_item().find(user_id) ==  _client->get_item().end() && puser_id != _profile->account().toStdString())
            //                continue;


            com.id = QString::fromLocal8Bit(item["id"].asCString());
            com.content = QString::fromLocal8Bit(item["content"].asCString());
            com.parent_id = QString::fromLocal8Bit(item["parent_id"].asCString());

            com.user_id = QString::fromLocal8Bit(item["user_id"].asCString());
            com.puser_id = QString::fromLocal8Bit(item["puser_id"].asCString());
            com.time = QString::fromLocal8Bit(item["time"].asCString());
            com.post_id = QString::fromLocal8Bit(item["post_id"].asCString());
            //name需要重组
            //            com.name =QString::fromLocal8Bit(item["user_id"].asCString());

            auto serach1 = _client->get_item().find(user_id);
            if(com.parent_id == "")
            {
                if(user_id == _profile->account().toStdString())
                {
                    com.name = _profile->nickname(); //表明是自己
                }else
                {
                    if(serach1 == _client->get_item().end())
                    {
                        //不是好友
                        com.name = com.user_id;
                    }else
                    {
                        com.name = com.name = _client->get_item()[user_id]->markname()==""?_client->get_item()[user_id]->nickname():_client->get_item()[user_id]->markname();
                    }
                }

            }else
            {
                auto serach2 =  _client->get_item().find(puser_id); //他的父对象是不是我好友
                if(user_id == _profile->account().toStdString())
                {
                    com.name = _profile->nickname() + " 回复 ";
                }else
                {
                    if(serach1 == _client->get_item().end())
                    {
                        //不是好友
                        com.name = com.puser_id + " 回复 ";
                    }else
                    {
                        com.name = com.name = _client->get_item()[user_id]->markname()==""?_client->get_item()[user_id]->nickname():_client->get_item()[user_id]->markname() + " 回复 ";
                    }
//                    com.name = _client->get_item()[user_id]->markname()==""?_client->get_item()[user_id]->nickname():_client->get_item()[user_id]->markname() + " 回复 ";

                }
                if(puser_id == _profile->account().toStdString())
                {
                    com.name += _profile->nickname();
                }else
                {
                    if(serach2 == _client->get_item().end())
                        com.name += com.puser_id;
                    else
                        com.name += _client->get_item()[puser_id]->markname()==""?_client->get_item()[puser_id]->nickname():_client->get_item()[puser_id]->markname();
                }


            }

            if(item["parent_id"] == "")
            {
                //表明这是一级评论
                _comment_model->add(com,_comment_model->rowCount());
            }else
            {
                //表明父_id有值，这是一个回复,找到父_id所在的位置
                int index = _comment_model->getIndex(item["parent_id"].asString());
                _comment_model->add(com,index);
                std::cout<<"index: :"<<index<<std::endl;
            }
        }
    }else
    {
        std::cout<<"解析失败"<<std::endl;
        exit(0);
    }
    std::cout<<"_comment_model->rowCount()"<<_comment_model->rowCount()<<std::endl;

}

void FC_Moments_Control::handle_comment_reply(const char *content, unsigned type)
{
    //不同的类型，处理方式不一样(1 普通回复，2 回复的回复)
    Json::Reader reader;
    Json::Value root;


    if(reader.parse(content,root))
    {
        //解析数据,先获得所有的数据
        string id,name,content,post_id,user_id,parent_id,time,puser_id;
        id = root["id"].asString();
        name = root["name"].asString();
        content = root["content"].asString();
        post_id = root["post_id"].asString();
        user_id = root["user_id"].asString(); //指的是评论人的user_id
        parent_id = root["parent_id"].asString();
        time = root["time"].asString();
        puser_id = root["puser_id"].asString();

        //现在来组合name

        Comment com;
        com.id = QString::fromLocal8Bit(id.c_str());
        com.content =QString::fromLocal8Bit(content.c_str());
        com.post_id = QString::fromLocal8Bit(post_id.c_str());
        com.user_id = QString::fromLocal8Bit(user_id.c_str());
        com.parent_id = QString::fromLocal8Bit(parent_id.c_str());
        com.puser_id = QString::fromLocal8Bit(puser_id.c_str());
        com.time = QString::fromLocal8Bit(time.c_str());
        if(type == 1)
        {
            //表明直接回复,直接显示user_id
           //查看这个user_id是不是好友，是好友则显示nickname(markname)否则显示account
            auto serach = _client->get_item().find(user_id);
            if(serach != _client->get_item().end())
            {
                //是好友
                com.name = _client->get_item()[user_id]->markname() == "" ? _client->get_item()[user_id]->nickname() : _client->get_item()[user_id]->markname();
            }else
            {
                //不是好友
                com.name = QString::fromLocal8Bit(user_id.c_str());

            }
            _comment_model->add(com,_comment_model->rowCount());
        }else if (type == 2)
        {
            //这里要处理

            //找存放的位置

            auto serach = _client->get_item().find(user_id);
            auto serach2 =  _client->get_item().find(puser_id); //他的父对象是不是我好友
            if(serach != _client->get_item().end())
            {
                //是好友
                com.name = _client->get_item()[user_id]->markname() == "" ? _client->get_item()[user_id]->nickname() : _client->get_item()[user_id]->markname();
                if(serach2 == _client->get_item().end())
                    com.name += com.puser_id;
                else
                    com.name += com.name += _client->get_item()[puser_id]->markname() == "" ? _client->get_item()[puser_id]->nickname() : _client->get_item()[puser_id]->markname();
            }else
            {
               com.name = com.user_id + " 回复 ";
               if(serach2 == _client->get_item().end())
                   com.name += com.puser_id;
               else
                   com.name += _client->get_item()[puser_id]->markname() == "" ? _client->get_item()[puser_id]->nickname() : _client->get_item()[puser_id]->markname();
            }
            int index = _comment_model->getIndex(parent_id);
            _comment_model->add(com,index);
        }


    }

}


