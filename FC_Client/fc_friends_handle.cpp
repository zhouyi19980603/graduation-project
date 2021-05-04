#include "fc_friends_handle.h"
#include "fc_message.h"
#include "fc_client.h"
#include "fc_message_handle.h"
#include "fc_buddyitem.h"
#include "fc_buddymodel.h"
#include "fc_buddyteam.h"
#include "fc_buddy.h"
#include "fc_friends_model.h"
#include <json/json.h>
#include <QDebug>
#include <filesystem>
#include <QVector>
#include <algorithm>
#include<iostream>
#include <unordered_map>
namespace fs = std::filesystem;


FC_Friends_Handle::FC_Friends_Handle(FC_Client *client, QObject *parent)
    :QObject(parent),_client(client)
{
    _model = BuddyModel::getInstance();
    _fmsModel = FMsgModel::getInstance();

//    _items["@12345"]=nullptr;
}

FC_Friends_Handle::~FC_Friends_Handle()
{
    cout<<"析构函数"<<endl;
}

void FC_Friends_Handle::search_friends(const QString &friendsAccount)
{

    string useacc = friendsAccount.toStdString();

//    if(_client->get_item().count(useacc))
//        cout<<"存在这个用户"<<endl;
//    else
//        cout<<"不存在这个用户"<<endl;
    //read qml to c++
//    cout<<"_items[useacc]->account().toStdString()"<<_items[useacc]->account().toStdString()<<endl;
    if(_client->get_item().count(useacc) ==0) //表明本地没有这个好友
    {
        char* account = (char*)malloc(friendsAccount.size()+1);
        memset(account,'\0',friendsAccount.size()+1);
        //QString to char*
        strcpy(account,friendsAccount.toLocal8Bit().data());
        qDebug()<<"test data: in handle"<<account<<"\n";
        FC_Message* fc_message= new FC_Message;
        fc_message->set_message_type(FC_FRIENDS_SEARCH);
        fc_message->set_body_length(strlen(account));
        fc_message->set_body(account,strlen(account));

        free(account);//记得释放内存，否则会报错
        _client->add_msg_to_socket(fc_message);
    }else
    {
        cout<<"有这个好友"<<endl;
        Buddy *buddy = Buddy::getInstance();
        buddy->clear();
        buddy->setAccount(_client->get_item()[useacc]->account());
        buddy->setHeading(_client->get_item()[useacc]->heading());
        buddy->setNickname(_client->get_item()[useacc]->nickname());
        buddy->setVisShow(true);
    }

}

void FC_Friends_Handle::add_friends(const QString &msg)
{
    qDebug()<<"add msg: "<<msg;
    char* account = (char*)malloc(msg.size()+1);
    memset(account,'\0',msg.size()+1);
    strcpy(account,msg.toLocal8Bit().data());//friends unique

    char* self = stringTochar(_client->getUniqueUserName());
    char* body = text_content(account,self);//好友在前，自己在后，合并在一起

    //消息
    FC_Message* message = new FC_Message;
    message->set_message_type(FC_FRIENDS_ADD);
    message->set_body_length(strlen(body));
    message->set_body(body,strlen(body));

    free(account);
    cout<<body<<endl;
    _client->add_msg_to_socket(message);
}

void FC_Friends_Handle::update_remark(const QString &team, const QString &item, const QString &user)
{
    for(int i=0;i<_model->teamCount();i++)
    {
        if(_model->team(i)->teamname() == team)
        {
            QVector<BuddyItem*>::iterator iter;
            //找到对应分组名

            for(iter = _model->team(i)->get_items().begin();iter != _model->team(i)->get_items().end();iter++)
            {
                if((*iter)->account() == item)
                {
                    (*iter)->setMarkname(user);
                    qDebug()<<"(*iter)->markname:"<<(*iter)->markname();
                }
            }break;
        }
    }
    string content = _client->getUniqueUserName() +'.'+item.toLocal8Bit().data()+'.'+user.toLocal8Bit().data();
    FC_Message* msg = new FC_Message;
    msg->set_message_type(FC_FRIENDS_REMARK);
    msg->set_body_length(content.size());
    msg->set_body(content.c_str(),msg->body_length());
    _client->add_msg_to_socket(msg);
}

void FC_Friends_Handle::delete_friend(const QString &team, const QString &item)
{
    for(int i=0;i<_model->teamCount();i++)
    {
        if(_model->team(i)->teamname() == team)
        {
            QVector<BuddyItem*>::iterator iter;
            //找到对应分组名

            for(iter = _model->team(i)->get_items().begin();iter != _model->team(i)->get_items().end();)
            {
                if((*iter)->account() == item)
                {
                    qDebug()<<"删除一个信息";
                    iter = _model->team(i)->get_items().erase(iter);

                }else
                    iter++;
            }
            break;
        }
    }

    emit _model->teamsChanged(); //发送信号，表明更改过
    //删除本地接口中的好友信息
    for(auto it = _client->get_item().begin();it != _client->get_item().end();)
    {
        if(it->first == item.toStdString())
            it = _client->get_item().erase(it);
        else
            it++;
    }

    FC_Message* msg = new FC_Message;
    msg->set_message_type(FC_DELETE_FRIENDS);
    msg->set_body_length(FC_ACC_LEN*2);
    msg->set_friend_identify(item.toStdString().c_str()); //好友标识
    msg->set_self_identify(_client->getUniqueUserName().c_str()); //个人标识
    _client->add_msg_to_socket(msg);
}

void FC_Friends_Handle::delete_friend(const string &account)
{
    cout<<" 删除好友： delete_friend(const string &account): "<<account<<endl;
    //删除本地接口中的好友信息
    for(auto it = _client->get_item().begin();it != _client->get_item().end();)
    {
        if(it->first == account)
            it = _client->get_item().erase(it);
        else
            it++;
    }

    for(int i=0;i<_model->teamCount();i++)
    {
        QVector<BuddyItem*>::iterator iter;
        for(iter = _model->team(i)->get_items().begin();iter != _model->team(i)->get_items().end();)
        {
            if((*iter)->account() == QString::fromLocal8Bit(account.c_str()))
            {
                iter = _model->team(i)->get_items().erase(iter);

                emit _model->teamsChanged(); //发送信号，表明更改过
                return;//退出去 不进行其他循环
            }else
            {
                iter++;
            }
        }

    }

}

void FC_Friends_Handle::validation_request(const QString &result)
{
    //验证请求是否ok
    if(result.toStdString() == "ok")
    {
        Buddy *buddy = Buddy::getInstance();

        BuddyItem* item = new BuddyItem ();
        item->setAccount(buddy->account());
        item->setHeading(buddy->heading());
        item->setNickname(buddy->nickname()); //一个单独的项

        for(int i=0;i<_model->teamCount();i++)
        {
            qDebug()<<_model->team(i)->teamname();
            if(_model->team(i)->teamname() == "friends")
            {
                QVector<BuddyItem*>::iterator iter;
                //找到对应分组名
                qDebug()<<"找到好友列表"<<_model->team(i)->teamname();
                _model->team(i)->appendItem(item);
                _model->teamsChanged();
                break;
            }
        }

        string acc = buddy->account().toStdString();
        _client->set_item(acc,item);
        FC_Message* message = new FC_Message;
        message->set_message_type(FC_FRIENDS_ADD_R);
        char* status = (char*) malloc(3);
        memset(status,'\0',3);
        strcpy(status,"ok"); //test data



        message->set_body_length(2*FC_ACC_LEN + strlen(status));  //?
        message->set_friend_identify(buddy->account().toStdString().c_str());//朋友标识
        message->set_self_identify(stringTochar(_client->getUniqueUserName()));//自己标识
        message->set_core_body(status,strlen(status));
        free(status);
        cout<<"message->body()"<<message->body()<<endl;
//        _client->add_msg_to_socket(message);
    }else
    {
        qDebug()<<"不同意添加为好友";
    }
}


void FC_Friends_Handle::displaytoQML(FC_Message *message)
{
    switch (message->mess_type()) {
    case FC_FRIENDS_SEARCH_R:   //搜索结果显示
        search_show(message->body());
        break;
    case FC_FRIENDS_ADD:      //添加好友结果
        qDebug()<<"我进来了 添加好友结果";
        add_friends_show(message->body());
//        add_friends_result(message->body(),"ok");
        //将添加信息发送给用户界面
        //
        break;
    }
}

void FC_Friends_Handle::refresh_friends_list(const string &msg)
{
    Json::Value root;
    Json::Reader reader;
    std::string acc;
    std::string nick;
    std::string heading;
    std::string sign;
    std::string sex;
    if(!reader.parse(msg, root)){
      std::cout <<"failed" <<std::endl;
     }
    else{
        acc = root["account"].asString();
        nick = root["nickname"].asString();
        sex = root["gender"].asString();
        sign = root["sign"].asString();
        heading = root["heading"].asString();
    }

    //保存在配置文件中
    _client->save_user_head(acc,heading);

    //得到整体当前文件所属的位置

    fs::path p = fs::current_path(); //目的是为了得到相对路径

    string path = "file://"+p.string()+"/assert/"+acc+".jpg";

    BuddyItem* item = new BuddyItem ();
    item->setAccount(QString::fromLocal8Bit(acc.c_str()));
    item->setHeading(QString::fromLocal8Bit(path.c_str()));
    item->setNickname(QString::fromLocal8Bit(nick.c_str()));
    item->setSign(QString::fromLocal8Bit(sign.c_str()));
    item->setGender(QString::fromLocal8Bit(sex.c_str()));

    _client->set_item(acc,item);
    for(int i=0;i<_model->teamCount();i++)
    {
        qDebug()<<_model->team(i)->teamname();
        if(_model->team(i)->teamname() == "friends")
        {
            QVector<BuddyItem*>::iterator iter;
            //找到对应分组名
            qDebug()<<"找到好友列表"<<_model->team(i)->teamname();
            _model->team(i)->appendItem(item);
            _model->teamsChanged();
            break;
        }
    }

}

void FC_Friends_Handle::parser_friends_json(const string &content)
{
    Json::Reader reader;
    Json::Value root;
    // reader将Json字符串解析到root，root将包含Json里所有子元素
    if (reader.parse(content, root))
    {
        cout<<"root asString():"<<root["username"].asString()<<endl;
        Json::Value items  = root["group"];
        for(int i=0;i<items.size();i++)
        {
             BuddyTeam* team = new BuddyTeam ();

            string teamname = items[i]["teamname"].asString();
            team->setTeamname(QString::fromLocal8Bit(teamname.c_str()));

            Json::Value item = items[i]["members"];
            for(int j=0;j<item.size();j++)
            {
                BuddyItem* buddyitem = new BuddyItem();

                string acc = item[j]["account"].asString();
                string nickname = item[j]["nickname"].asString();
                _client->save_user_head(acc,item[j]["heading"].asString());
                fs::path p = fs::current_path(); //目的是为了得到相对路径
                string path = "file://"+p.string()+"/assert/"+acc+".jpg";
                string markname = item[j]["markname"].asString();
                string gender = item[j]["gender"].asString();
                string sign = item[j]["sign"].asString();


                buddyitem->setMarkname(QString::fromLocal8Bit(markname.c_str()));
                buddyitem->setAccount(QString::fromLocal8Bit(acc.c_str()));
                buddyitem->setNickname(QString::fromLocal8Bit(nickname.c_str()));
                buddyitem->setHeading(QString::fromLocal8Bit(path.c_str()));
                buddyitem->setGender(QString::fromLocal8Bit(gender.c_str()));
                buddyitem->setSign(QString::fromLocal8Bit(sign.c_str()));
                team->appendItem(buddyitem);

                _client->set_item(acc,buddyitem);
//                _items[acc] = buddyitem; //这里容器存放的是好友信息
            }
            _model->appendTeam(team);
        }
        emit _model->teamsChanged();
    }
}

unordered_map<string, BuddyItem *> &FC_Friends_Handle::get_item()
{
    return _items;
}

void FC_Friends_Handle::set_item(string &acc, BuddyItem *item)
{
    _items[acc] = item;
}


void FC_Friends_Handle::search_show(const string &msg)
{
    Buddy *buddy = Buddy::getInstance();
    buddy->clear();
    if(strcmp(msg.c_str(),"error\0") == 0 )
    {
        qDebug()<<"没有这个好友信息"<<"\n";
    }else{
        Json::Value root;
        Json::Reader reader;
        std::string acc;
        std::string nick;
        std::string heading;
        if(!reader.parse(msg, root)){
          std::cout <<"failed" <<std::endl;
        }else{
            acc = root["account"].asString();
            nick = root["nickname"].asString();
            heading = root["heading"].asString();
        }
        _client->save_user_head(acc,heading); //保存图片

        fs::path p = fs::current_path(); //目的是为了得到相对路径
        string path = "file://"+p.string()+"/assert/"+acc+".jpg";

        buddy->setAccount(QString::fromLocal8Bit(acc.c_str()));
        buddy->setNickname(QString::fromLocal8Bit(nick.c_str()));
        buddy->setHeading(QString::fromLocal8Bit(path.c_str())); //设置了相应的数据

        qDebug()<<buddy->account()<<" "<<buddy->heading()<<" "<<buddy->nickname();
    }

}

void FC_Friends_Handle::add_friends_show(const string &msg)
{
    Json::Value root;
    Json::Reader reader;
    std::string acc;
    std::string nick;
    std::string heading;
    std::string sign;
    std::string sex;
    if(!reader.parse(msg, root)){
      std::cout <<"failed" <<std::endl;
    }
    else{
        acc = root["account"].asString();
        nick = root["nickname"].asString();
        sex = root["gender"].asString();
        sign = root["sign"].asString();
        heading = root["heading"].asString();
    }

    //保存在配置文件中
    _client->save_user_head(acc,heading);

    //得到整体当前文件所属的位置

    fs::path p = fs::current_path(); //目的是为了得到相对路径

    string path = "file://"+p.string()+"/assert/"+acc+".jpg";

    FMsg fmsg;
    fmsg.name = QString::fromLocal8Bit(nick.c_str());
    fmsg.account = QString::fromLocal8Bit(acc.c_str());
    fmsg.heading = QString::fromLocal8Bit(path.c_str());
    fmsg.content = "ignore";

    _fmsModel->insert(fmsg);

//    Buddy *buddy = Buddy::getInstance();
//    buddy->setAccount(QString::fromLocal8Bit(acc.c_str()));
//    buddy->setNickname(QString::fromLocal8Bit(nick.c_str()));
//    buddy->setHeading(QString::fromLocal8Bit(path.c_str())); //设置了相应的数据
//    buddy->setValue("1"); //直接传入1目前,表明有数据
}

char *FC_Friends_Handle::text_content(const char *account, const char *pass)
{
    std::cout<<"account"<<account<<std::endl;
    std::cout<<"password"<<pass<<std::endl;
    int n = strlen(account)+strlen(pass)+1;
    char * ret = (char*) malloc(n);
    memset(ret,'\0',n);
    memcpy(ret,account,strlen(account));
    memcpy(ret+strlen(account),pass,strlen(pass));
    return ret;
}

string FC_Friends_Handle::QStrTostr(QString &qstr)
{
    return (const char*)qstr.toLocal8Bit();
}

char *FC_Friends_Handle::stringTochar(const string &str)
{
    char* buff = (char*)malloc(str.size()+1);
    memset(buff,'\0',str.size()+1);
    strcpy(buff,str.c_str());
    return buff;
}
