#include "fc_message_handle.h"
#include "fc_message.h"
#include "fc_server.h"
#include "fc_message.h"
#include "fc_header.h"
#include "fc_connection.h"
#include "fc_server.h"
#include <cstring>
#include <QDebug>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/thread.hpp>
#include <QSqlQuery>
#include "fc_db_proxy.h"
#include "./Moments/fc_concretemoments.h"
#include "./Moments/fc_viewer.h"
#include <random>



using namespace boost::property_tree;

//==============================================
//  public function
//==============================================



FC_Message_Handle::FC_Message_Handle(FC_Server* server,FC_Connection *connection )
    :_server(server),_connection(connection)
{
    redisInit();
}

//初始化redis数据库
void FC_Message_Handle::redisInit()
{
    struct timeval timeout = {1,500000};
    const char* ip = "127.0.0.1";
    int port = 6379;
    _content = redisConnectWithTimeout(ip,port,timeout);
    if(_content == nullptr || _content->err){
        if(_content){
            cout<<"Connection error: "<<_content->errstr<<endl;
        }else{
            cout<<"Connection error: can't allocate redis context\n";
        }
        exit(1);
    }
}

FC_Message_Handle::~FC_Message_Handle()
{
    redisFree(_content);//释放redis的连接
}

void FC_Message_Handle::handle_header(FC_Message *message){
    message->set_body_length(message->body_length());
}

void FC_Message_Handle::handle_body(FC_Message* message){
    unsigned type = message->mess_type();
    //according message type handle message
    if(type&FC_PROFILE){
        switch (type) {
        case FC_SIGN_IN:
            handle_sign_in(message->body());
            break;
        case FC_UPDATE_NICK:
            update_nick(message->body());
            break;
        case FC_UPDATE_SEX:
            update_gender(message->body());
            break;
        case FC_UPDATE_HEAD:
            cout<<"修改头像"<<endl;
            update_heading(message);
            break;
        case FC_REGISTER :
            handle_register(message);
            break;
        default:
            cout<<"没有这样的类型"<<endl;
            break;
        }
    }else if(type & FC_FRIENDS){
        switch (type) {
        case FC_DELETE_FRIENDS:
            cout<<"删除好友"<<endl;
            delete_friend(message);
            break;
        case FC_FRIENDS_REMARK:
            cout<<"好友信息（备注）"<<endl;
            handle_remark(message->body());
            break;
        case FC_FRIENDS_SEARCH:
            std::cout<<"查询好友信息"<<std::endl;
            friends_search_handle(message->body()); //传入消息body
            break;
        case FC_FRIENDS_ADD:
            cout<<"add friends"<<endl;
            add_friends(message);
            //添加好友信息
            break;

        case FC_FRIENDS_ADD_R:
            cout<<"反馈消息"<<endl;
            if(strcmp(message->get_core_body(),"ok\0") == 0)
            {
                cout<<"同意添加好友"<<endl;
                add_friends_lists(message);
            }
            else{
                cout<<"这是不同意添加好友"<<endl;
            }
            break;
        default:
            cout<<"好友没有这样的类型"<<endl;
            break;
        }
    }else if(type & FC_MESSAGES){
        switch (type) {
        case FC_TEXT_MEG:
            handle_text_msg(message);
            break;
        case FC_GROUP_TEXT_MEG:
           // handle_group_text_msg(message);
            break;
        case FC_FILE_MEG:
            //目前为直接转发，暂时不做存储
            handle_file_msg(message);
            cout<<"处理文件"<<endl;
            break;
        default:
            cout<<"聊天没有这样的类型"<<endl;
            break;
        }
    }else if(type & FC_MOMENTS){
        switch (type) {
        case FC_LIKE:  //点赞
            cout<<"点赞消息"<<endl;
            handle_like_message(message->body());
            break;
        case FC_COMMENT: //评论
            break;
        case FC_NEW_MOMENTS: //发布消息
            handle_new_moments(message->body());
            break;
        case FC_REQUEST_DY:
            handle_request_dy(message->body());
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



FC_Message* FC_Message_Handle::generate_message(unsigned type,const char* content){

    FC_Message* message = new FC_Message;//delete in on_write()
    unsigned msg_size = strlen(content)+1;
    message->set_header(type,msg_size);
    message->set_body(content,msg_size);
    return message;
}


void FC_Message_Handle::send_self_msg(const string &username)
{
    std::string str ;
    str = make_json_user(username);

    FC_Message* msg = new FC_Message;
    msg->set_message_type(FC_SELF_MES);

    clog << "make_json::body_size():" << str.size() << endl;
    msg->set_body_length(str.size());
    msg->set_body(str.c_str(),str.size());
    _server->forward_message(username,msg);
}

void FC_Message_Handle::send_friends_lists(const string &username)
{
    std::string str ;
    str = make_json(username);
    FC_Message* msg = new FC_Message;
    msg->set_message_type(FC_FRIENDS_MESSAGE);

    clog << "make_json::body_size():" << str.size() << endl;
    msg->set_body_length(str.size());
    msg->set_body(str.c_str(),str.size());
    _server->forward_message(username,msg);
}

string FC_Message_Handle::make_json(string username)
{
    DbBroker* _broker = new DbBroker ();
    QSqlQuery qu = _broker->get_friends_list(QString::fromStdString(username));

    QHash<QString,QString> _hash;
    while (qu.next()) {
        _hash[qu.value(1).toString()] = qu.value(1).toString();
    }

    QString user = QString::fromStdString(username);
    ptree writeroot;
    ptree groups,pt_allitem;

    ptree pt_item;
    QHashIterator<QString,QString> _iter(_hash);
    while (_iter.hasNext()) { //分组
        _iter.next();
        //select* from friends_info where user_id='@12345' and group_name='friends';
        QString query = "select* from friends_info where user_id='"+user+"' and group_name='"+_iter.value()+"'";
        QSqlQuery group = _broker->self_query(query); //分组
        ptree members;
        while (group.next()) { //得到每一个分组的信息
            QSqlQuery item = _broker->get_user_msg(group.value(1).toString());
            item.next();
            ptree subitem;
            subitem.put("account",item.value(0).toString().toStdString());
            subitem.put("nickname",item.value(1).toString().toStdString());
            subitem.put("markname",group.value(3).toString().toStdString());
            subitem.put("sign",item.value(3).toString().toStdString());
            string filepath = item.value(2).toString().toStdString();//得到相应的文件路径
            string content = handle_user_head(filepath); //处理头像函数
            subitem.put("heading",content); //发送用户头像二进制文件
            //            subitem.put("heading",item.value(2).toString().toStdString()); //这里发送的是路径，现在需要对其进行修改
            subitem.put("gender",item.value(4).toString().toStdString());

            _server->get_friends_list()[username].clear();
            _server->set_friendsL(username,item.value(0).toString().toStdString());

            members.push_back(make_pair("",subitem));
        }
        pt_item.put("teamname",_iter.value().toStdString());
        pt_item.put_child("members",members);
        groups.push_back(make_pair("",pt_item));
    }
    pt_allitem.put("username",username);
    pt_allitem.put_child("group",groups);


    std::stringstream ss;
    boost::property_tree::write_json(ss, pt_allitem);
    std::string strContent = ss.str();
    return strContent;
}

string FC_Message_Handle::make_json_user(const string &username)
{
    DbBroker* _broker = new DbBroker ();
    QSqlQuery qu =_broker->get_user_msg(QString::fromStdString(username));
    qu.next();

    ptree writeroot;
    //还需要传入account nickname  heading sign gender
    string filepath = qu.value(2).toString().toStdString();//得到相应的文件路径

    string content = handle_user_head(filepath); //处理头像函数

    writeroot.put("account",qu.value(0).toString().toStdString());
    writeroot.put("nickname",qu.value(1).toString().toStdString());
    writeroot.put("heading",content);
    writeroot.put("sign",qu.value(3).toString().toStdString());
    writeroot.put("gender",qu.value(4).toString().toStdString());

    std::stringstream ss;
    boost::property_tree::write_json(ss, writeroot);
    std::string strContent = ss.str();
    delete _broker; //释放空间
    return strContent;
}

void FC_Message_Handle::update_nick(const char *s)
{
    char* account = new char[FC_ACC_LEN+1];
    memset(account,'\0',FC_ACC_LEN+1);
    memcpy(account,s,FC_ACC_LEN); //读取长度

    char* content = new char[strlen(s)-FC_ACC_LEN+1];
    memset(content,'\0',strlen(s)-FC_ACC_LEN+1);
    memcpy(content,s+FC_ACC_LEN,strlen(s)-FC_ACC_LEN);

    if(_server->update_nick(account,content))
    {
        FC_Message* msg = new FC_Message;
        msg->set_message_type(FC_UPDATE_NICK);
        msg->set_body_length(strlen(content));
        msg->set_body(content,strlen(content));
        //        do_write(msg);
        _server->forward_message(account,msg);
    }
    else
    {
        std::cout <<"update_nick failed:"<<endl;
    }
    delete [] account;
    delete [] content;
}

void FC_Message_Handle::update_gender(const char *s)
{
    char* account = new char[FC_ACC_LEN+1];
    memset(account,'\0',FC_ACC_LEN+1);
    memcpy(account,s,FC_ACC_LEN); //读取长度

    char* content = new char[strlen(s)-FC_ACC_LEN+1];
    memset(content,'\0',strlen(s)-FC_ACC_LEN+1);
    memcpy(content,s+FC_ACC_LEN,strlen(s)-FC_ACC_LEN);

    if(_server->update_gender(account,content))
    {
        FC_Message* msg = new FC_Message;
        msg->set_message_type(FC_UPDATE_SEX);
        msg->set_body_length(strlen(content));
        msg->set_body(content,strlen(content));
        _server->forward_message(account,msg);
    }
    else
    {
        std::cout <<"update_nick failed:"<<endl;
    }
    delete [] account;
    delete [] content;
}

void FC_Message_Handle::update_heading(FC_Message *msg)
{
    Json::Value root;
    Json::Reader reader;
    string acc;
    string head;
    if(!reader.parse(msg->body(),root))
    {
        std::cout <<"failed" <<std::endl;
    }else
    {
        head= root["heading"].asString();
        acc = root["account"].asString();

    }
    if(save_user_head(acc,head))
    {
        std::cout <<"update_heading succeed:"<<endl;
        _server->forward_message(acc,msg);
    }else
    {
        std::cout <<"update_heading failed:"<<endl;
    }

}

void FC_Message_Handle::friends_search_handle(const char *s)
{

    FC_Message* message = new FC_Message;
    message->set_message_type(FC_FRIENDS_SEARCH_R); //返回查找好友列表
    //先判断是否在accounts中，如果在的话，在判断是否在在线列表中，若在的话直接发送，不再的话就发送在离线列表中，等用户上线
    if(_server->get_accounts().count(s) !=0 && _server->get_onlineP()[s] != _connection) //condition is error
    {
        DbBroker* broker = new DbBroker ();
        QSqlQuery query =  broker->get_user_msg(QString::fromStdString(s)); //得到用户信息
        query.next();
        ptree writeroot;

        std::string username = query.value(0).toString().toStdString(); //返回给客户端帐号，昵称，以及用户头像
        std::string nick = query.value(1).toString().toStdString();
        std::string filepath = query.value(2).toString().toStdString();
        string content = handle_user_head(filepath); //处理头像函数

        writeroot.put("account",username);
        writeroot.put("nickname",nick);
        writeroot.put("heading",content);

        std::stringstream ss;
        boost::property_tree::write_json(ss, writeroot);
        std::string strContent = ss.str();
        message->set_body_length(strContent.size());
        message->set_body(strContent.c_str(),strContent.size());

        delete broker;
    }
    else
    { //not exist
        cout<<"not exist"<<endl;
        //        message->set_message_type(FC_FRIENDS_SEARCH_R);

        std::string msg = "error";
        char* buff = (char*)malloc(msg.size()+1);
        memset(buff,'\0',msg.size()+1);
        strcpy(buff,msg.c_str());
        message->set_body_length(msg.size()); // memory
        message->set_body(buff,msg.size());

        free(buff);
    }
    _connection->write(message);

}

void FC_Message_Handle::add_friends(FC_Message *msg)
{
    //这接消息转发给了服务端
    char* sd = msg->get_self_identify();//添加好友端的标识
    char* rv = msg->get_friends_identify(); //发送给好友的id

    std::string str ;
    str = make_json_user(sd);

    FC_Message* message = new FC_Message;
    message->set_message_type(FC_FRIENDS_ADD);
    message->set_body_length(str.size()); //发送了用户相关的所有信息
    message->set_body(str.c_str(),str.size());

    if(_server->get_onlineP().count(rv) !=0) //对方在线
        _server->forward_message(rv,message);
    else
        _server->set_offlineM(rv,message);

    cout<<"get_offlineM().size():"<<_server->get_offlineM().size()<<std::endl;

}

void FC_Message_Handle::add_friends_lists(FC_Message *msg)
{
    char* one = msg->get_friends_identify(); //one是自己的
    char* two = msg->get_self_identify(); //two是好友的

    DbBroker* broker = new DbBroker ();
    if(broker->add_friends(QString::fromStdString(one),QString::fromStdString(two)))
    {
        std::cout<<"add_friends_lists: success"<<endl;
    }
    //send message to client

    delete broker;
    std::string str ;
    str = make_json_user(two); //查询好友的用户信息
    msg->set_body_length(str.size());
    msg->set_body(str.c_str(),str.size());
    _server->forward_message(one,msg);
}

void FC_Message_Handle::delete_friend(FC_Message* msg)
{
    string friends;
    string account;

    friends = msg->get_friends_identify();
    account = msg->get_self_identify();

    cout<<"friends:"<<friends<<endl;

    if(_server->delete_friends(QString::fromStdString(account),QString::fromStdString(friends)))
    {
        std::cout<<"删除好友成功"<<std::endl;
    }

}

void FC_Message_Handle::handle_remark(const char *s)
{
    string friends;
    string account;
    string remark;

    stringstream input(s);
    getline(input,account,'.');
    getline(input,friends,'.');
    getline(input,remark,'.');

    if(_server->update_mark(QString::fromStdString(account),QString::fromStdString(friends),QString::fromStdString(remark)))
    {
        std::cout<<"修改备注成功"<<std::endl;
    }
}

void FC_Message_Handle::handle_offlineM(const string &acc)
{
    //处理离线消息
    if(_server->get_offlineM().count(acc) !=0 )
    {
        while (!_server->get_offlineM()[acc].empty()) {
            qDebug()<<"存在离线消息";
            _server->forward_message(acc,_server->get_offlineM()[acc].front()); //取队头元素
            _server->get_offlineM()[acc].pop(); //弹出队头元素
        }
    }
}


//==============================================
//  private function
//==============================================


void FC_Message_Handle::handle_ordinary_msg(FC_Message* message){

}
void FC_Message_Handle::handle_sign_in(const char* s){
    char* account = new char[FC_ACC_LEN+1];
    memset(account,'\0',FC_ACC_LEN+1);
    memcpy(account,s,FC_ACC_LEN);

    char* password = new char[strlen(s)-FC_ACC_LEN+1];
    memset(password,'\0',strlen(s)-FC_ACC_LEN+1);
    memcpy(password,s+FC_ACC_LEN,strlen(s)-FC_ACC_LEN); //得到账户和密码

    qDebug()<<account<<":"<<password;
    if(_server->login_verify(account,password) && _server->repeat_login(account,_connection))
    {
        FC_Message* msg = generate_message(FC_SIGN_IN_R,"ok");
        _connection->write(msg);
        this->_server->add_identified(account,this->_connection); //添加在在线列表中
        send_self_msg(account);
        send_friends_lists(account);
        handle_offlineM(account);
        send_history(account);
    }else
    {
        FC_Message* msg = generate_message(FC_SIGN_IN_R,"error");
        _connection->write(msg);
    }
    //    qDebug() << s << "has singed in";
}

void FC_Message_Handle::handle_register(FC_Message *msg) //里面为昵称和密码
{
    string unique;
    while(1)
    {
        unique = random_account();//生成随机帐号
        if(_server->get_accounts().count(unique)==0)
        {
            FC_Message* message = generate_message(FC_REGISTER_R,unique.c_str());
            _connection->write(message);
            //分配帐号成功,返回给客户端
            //存入信息在服务端
            break;
        }
        //如果已经存在改帐号则继续分配
    }
    string nick;
    string pass;
    stringstream input(msg->body());
    getline(input,nick,'\t');
    getline(input,pass,'\t');
    _server->set_accounts(unique,pass); //存入账户列表

    QString nickname = QString::fromLocal8Bit(nick.c_str());
    QString password = QString::fromLocal8Bit(pass.c_str());

    DbBroker* broker = new DbBroker();
    if(broker->add_user(nickname,password,QString::fromStdString(unique)))
        cout<<"注册成功"<<endl;
    else
        cout<<"注册在数据库中失败"<<endl;

}
void FC_Message_Handle::send_history(const string &userId)
{

    Json::Reader reader;
    Json::Value root;

    //从文件中读取，保证当前文件有demo.json文件
    ifstream infile("history/"+userId+".json", ios::binary);

    if (!infile.is_open())
    {
        cout << "Error opening json file\n";
        return;
    }
    ostringstream buf;
    char ch;
    while(buf &&infile.get(ch))
    {
      buf.put(ch);
    }
    infile.close();
    string tmpContent = buf.str();
//    qDebug() <<"json  读取数据打印:"<<tmpContent.c_str();
    FC_Message* tmp = generate_message(FC_TEXT_MEG_HISTORY,tmpContent.c_str());
    this->_connection->write(tmp);

}

void FC_Message_Handle::handle_text_msg(FC_Message* msg){
    char s_account[FC_ACC_LEN];  //保存消息接受者账号
    memcpy(s_account,msg->header()+14,FC_ACC_LEN);  //4+4+6
    char *content = msg->body();
    //确定好友是否在先在决定是否发送消息
    this->_server->forward_message(string(s_account),msg);
    std::cout<< s_account<<std::endl;
    std::cout<<content<<std::endl;
    get_file_path(msg);
}

void FC_Message_Handle::handle_file_msg(FC_Message *msg)
{
    _server->forward_message(msg->get_friends_identify(),msg);
}

//随机生成6位帐号信息
string FC_Message_Handle::random_account()
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, 9);

    string account;
    for (int n=0; n<6; ++n)
    {
        int dice_roll = dis(gen);
        account += std::to_string(dice_roll);
    }
    return account;
}
void FC_Message_Handle::handle_group_text_msg(FC_Message *msg)
{


    char* w_account =new char[7];    //保存消息接受者账号(群账号)
    memset(w_account,'\0',7);
    char* m_account =new char[7];    //保存消息接受者账号(群账号)
    memset(m_account,'\0',7);
    memcpy(w_account,msg->header()+8,FC_ACC_LEN);
    memcpy(m_account,msg->header()+14,FC_ACC_LEN);
    char *content = msg->body()+12;  //消息内容
    qDebug()<<"群消息: "<<content;

    this->_server->forward_group_message(string(m_account),string(w_account),msg);
    free(m_account);
    free(w_account);

}

void FC_Message_Handle::handle_new_moments(const char* content)
{
    Json::Value root;
    Json::Reader reader;
    string acc,postId;
    if(!reader.parse(content,root))
    {
        std::cout <<"failed" <<std::endl;
        exit(0);
    }else
    {
        acc = root["userId"].asString(); //得到用户id
        postId = root["dyId"].asString();
    }

    DbBroker* broker = new DbBroker();
    if(broker->add_post(QString::fromStdString(acc),QString::fromStdString(postId))){
        //添加到json文件中
        string filename = "./config/moments.json";

        Json::Value item;
        item["con_text"] = root["con_text"];//文本内容
        item["con_image"] = root["con_image"];//图片
        item["time"] = root["time"];//时间
        item["user_id"] = root["userId"];
        item["post_id"] = root["dyId"];
        add_json_data(item,filename,postId,1);//里面的图片直接保存的二进制图片,1表示对象

        item.clear();//清空
        item["post_id"] = root["dyId"];
        filename = "./config/user_moments.json";
        //保存在user_moments中
        add_json_data(item,filename,acc,2);//2表示数组
        //添加进redis中
        _reply = (redisReply*)redisCommand(_content,"hset %s %s %s",postId.c_str(),"user_id",acc.c_str());
        freeReplyObject(_reply);
        //在这里去填充观察者
        Subject* moments = new ConcreteMoments ();

        moments->clearObserver();
        //得到所有的列表
        for(auto each : _server->get_friends_list()[acc])
        {
            Observer* observer = new Viewer (_server,each);
            moments->registerObserver(observer);//注册进去
        }
        moments->setContent(content,FC_NEW_MOMENTS);
    }else
    {
        std::cout<<"add post failed"<<std::endl;
    }


}

//就可以直接查询redis中来确定user_id即可
void FC_Message_Handle::handle_like_message(const char *content)
{
    Json::Value root;
    Json::Reader reader;
    string dyId,userId,userNickname;
    if(!reader.parse(content,root))
    {
        exit(0);
    }else
    {
        dyId = root["dyId"].asString();
        userId = root["userId"].asString();
        userNickname = root["userNick"].asString();
    }
    //这里的userId指的是点赞的用户id
    update_json_like_data(userId,dyId);
    //通过dyId，查找对应的authorId，这里就会开始使用redis
    _reply = (redisReply*)redisCommand(_content,"hget %s user_id",dyId.c_str());


//    add_json_data()
    //得到点赞消息后存入对应的moments.json中（post_id）
    Subject* moments = new ConcreteMoments ();

    moments->clearObserver();
    //得到所有的列表
    std::cout<<"handle_like_message:"<<_reply->str<<std::endl;
    std::cout<<_server->get_friends_list()[_reply->str].size()<<std::endl;
    for(auto each : _server->get_friends_list()[_reply->str])
    {
        Observer* observer = new Viewer (_server,each);
        moments->registerObserver(observer);//注册进去
    }
    moments->setContent(userNickname,FC_LIKE);//只传送nickname进去
    //找到user_id向user_id发送通知有人点赞（这里面进行处理），向user_id的所有好友发送这个点赞通知
    //_reply->str;//得到对应的值user_id,在里面加一个对应的类型即可
}

void FC_Message_Handle::handle_request_dy(const char *content)
{
    //得到userid，现在所在的content就是userid，通过userid，找到好有,发送10条过去
    //从json中读取来放在redis中
    //先读取user_moments中的内容
    Json::Reader reader1,reader2;
    Json::Value root1,root2;
    string filename1 = "./config/user_moments.json";
    string filename2 = "./config/moments.json";
    ifstream is1,is2;
    is1.open(filename1,std::ios::binary);
    is2.open(filename2,std::ios::binary);


    //写过客户端
    Json::FastWriter write;
    Json::Value writeRoot;
    if(!reader2.parse(is2,root2))
    {
        cout<<"reader解析失败"<<endl;
        exit(0);
    }
    if(reader1.parse(is1,root1))
    {
        Json::Value item;
        //读取两条信息发出去,消息条数可以自己控制
        for(int i=0;i<root1[content].size();i++)
        {
            string postId = root1[content][i]["post_id"].asString();
            std::cout<<"handle_request_dy: "<<postId<<std::endl;
            //查找另一个文件
            writeRoot["moments"].append(root2[postId]);
        }

    }
    string contents = write.write(writeRoot);
    FC_Message* message = generate_message(FC_REPLY_DY,contents.c_str());
    this->_connection->write(message);
    is1.close();
    is2.close();
}

std::string FC_Message_Handle::handle_user_head(const string &filepath)
{
    // 1. 打开图片文件
    ifstream is(filepath, ifstream::in | ios::binary);

    if(!is.is_open())
    {
        cout<<"open failed"<<endl;
        exit(0);
    }
    // 2. 计算图片长度
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);
    // 3. 创建内存缓存区
    char * buffer = new char[length];
    // 4. 读取图片
    is.read(buffer, length);
    string content(buffer,length);
    is.close();
    delete [] buffer;
    return content;
}

bool FC_Message_Handle::save_user_head(const string &acc, const string &heading)
{
    //保存在配置文件中
    std::string filepath = "./assert/"+acc+".jpg";

    std::ofstream fout(filepath, std::ios::binary);
    if(!fout)
    {
        std::cout<<"open failed";
        return false;
    }
    fout.write(heading.data(), heading.size());
    fout.close();
    return true;
}

void FC_Message_Handle::add_json_data(Json::Value item, const string &filename,const string& key,unsigned type)
{
    Json::Reader reader;
    Json::Value root;
    ifstream is;

    is.open(filename,std::ios::binary);
    if(reader.parse(is,root,false))
    {

        if(type == 1)
            root[key] = item;
        else if(type == 2)
            root[key].append(item);

        Json::FastWriter write;
        string strWrite = write.write(root);
        ofstream ofs;
        ofs.open(filename);
        ofs << strWrite;
        ofs.close();
    }
    is.close();
}

void FC_Message_Handle::update_json_like_data(const string& item,const string& key)
{
    Json::Reader reader;
    Json::Value root;
    ifstream is;

    string filename = "./config/moments.json";
    is.open(filename,std::ios::binary);
    if(reader.parse(is,root,false))
    {
        root[key]["likes"].append(item);
        Json::FastWriter write;
        string strWrite = write.write(root);
        ofstream ofs;
        ofs.open(filename);
        ofs << strWrite;
        ofs.close();
    }
    is.close();
}

//端对端存储
void FC_Message_Handle::store_history(FC_Message* msg,const string& path)
{
    char content[msg->body_length()+1];
    memset(content,'\0',msg->body_length()+1);
    memcpy(content,msg->body(),msg->body_length());

    if(!is_file_exist(path)){
        //根节点
        Json::Value root;
        //msgContent数组下,每个元素对应一条message
        root["msgContent"].append(content);

        //缩进输出
        cout << "StyledWriter:" << endl;
        Json::FastWriter fw;
        cout << fw.write(root) << endl << endl;

        //输出到文件
        ofstream os;
        os.open(path, std::ios::out | std::ios::binary);
        if (!os.is_open())
            cout << "error：can not find or create the json file" << endl;
        os << fw.write(root);
        os.close();
    }else{
        Json::Reader reader;//读文件
        Json::Value root;
        //从文件中读取，保证当前文件有demo.json文件
        ifstream infile(path, ios::binary);

        if (!infile.is_open())
        {
            cout << "Error opening json file\n";
            return;
        }
        ostringstream buf;
        char ch;
        while(buf &&infile.get(ch)){
            buf.put(ch);
        }
        infile.close();
        string tmpContent = buf.str();
        if(reader.parse(tmpContent, root, false) == true){
            root["msgContent"].append(content);
        }

        cout << "StyledWriter:" << endl;
        Json::FastWriter fw;
        cout << fw.write(root) << endl << endl;
        //输出到文件
        ofstream os;
        os.open(path, std::ios::out | std::ios::binary);
        if (!os.is_open())
            cout << "error：can not find or create the json file" << endl;
        os << fw.write(root);
        os.close();
    }
}
string FC_Message_Handle::get_file_path(FC_Message *msg)
{
    char* w_account =new char[7];    //保存消息接受者账号
    memset(w_account,'\0',7);
    char* m_account =new char[7];    //保存消息接受者账号
    memset(m_account,'\0',7);
    memcpy(w_account,msg->header()+8,FC_ACC_LEN);
    memcpy(m_account,msg->header()+14,FC_ACC_LEN);
    string f1 = m_account;
    string f2 = w_account;
    string filePath1 = "./history/"+f1+".json";
    string filePath2 = "./history/"+f2+".json";

    store_history(msg,filePath1);    //两个账号各存一份消息
    store_history(msg,filePath2);

}

//检验历史文件是否存在
bool FC_Message_Handle::is_file_exist(const string &name)
{
    return (access( name.c_str(), F_OK ) != -1 );
}

