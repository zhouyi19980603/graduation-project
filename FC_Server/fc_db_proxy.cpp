#include "fc_db_proxy.h"
#include "fc_database.h"
#include <QDebug>



DbBroker::DbBroker(FC_Server *server)
    :_server(server)
{
    db = new FC_DataBase;
}

DbBroker::~DbBroker()
{
    delete db;
}

bool DbBroker::queryIsNotExist(const QString &sql)
{
    qDebug() <<"come in";
    QString query = "select* from account_info where account=\"@12345\" and password=\"12345\"";
    return db->isQueryExist(query);
}

QSqlQuery DbBroker::get_user_account()
{
    QString query = "select* from account_info";
    return db->query(query);
}

QSqlQuery DbBroker::get_user_msg(const QString &account)
{
    QString query = "select* from user_message_info where account ='"+account+ "'";
    return db->query(query);
}

QSqlQuery DbBroker::get_friends_list()
{
    QString query = "select* from friends_info";
    return db->query(query);
}

QSqlQuery DbBroker::self_query(const QString &ery)
{
    return db->query(ery);
}

QSqlQuery DbBroker::get_friends_list(const QString &account)
{
    QString query = "select* from group_info where user_id='"+account+"'";
    return db->query(query);//返回登录用户的好友列表
}

bool DbBroker::update_nick(const QString &acc, const QString &nick)
{
    //update user_message_info set nickname='LOVE' where account = '@12345';
    QString query = "update user_message_info set nickname='"+nick+"' where account = '"+acc+"'";
    return db->update(query);
}

bool DbBroker::update_gender(const QString &acc, const QString &sex)
{
    QString query = "update user_message_info set gender='"+sex+"' where account = '"+acc+"'";
    return db->update(query);
}

bool DbBroker::update_mark(const QString &user_id, const QString &friend_id, const QString &mark)
{
    //update friends_info set markname ='zhouyi' where user_id='@12345' and friend_id='@13456';
    QString query = "update friends_info set markname ='"+mark+"' where user_id='"+user_id+"' and friend_id='"+friend_id+"'";
    return db->update(query);
}

bool DbBroker::delete_friends(const QString &user_id, const QString &friend_id)
{
    //delete from friends_info where user_id='@12345' and friend_id='@13456';
    QString query = "delete from friends_info where user_id='"+user_id+"' and friend_id='"+friend_id+"'";
    return db->move(query);
}

bool DbBroker::add_friends(const QString &user_id, const QString &friends_id)
{
    return db->insert(user_id,friends_id);
}

bool DbBroker::serach_friend(const QString &account)
{
    //    QString query = ""
}

bool DbBroker::add_user(const QString &nick, const QString &pass, const QString &acc)
{
    //insert into account_info (account,password) values ('12345','45678')
    QString query1 ="insert into account_info (account,password) values ('"+acc+"','"+pass+"')"; //插入在用户表中
    //insert into user_message_info(account,nickname,sign) values('123456','LLOIU','');
    QString query2 = "insert into user_message_info(account,nickname,sign) values('"+acc+"','"+nick+"','')";
    //insert into group_info(user_id,group_name) values('123456','friends');
    QString query3 = "insert into group_info(user_id,group_name) values('"+acc+"','friends')";
    return db->insert(query1) && db->insert(query2) && db->insert(query3);
}

bool DbBroker::add_post(const QString &user_id, const QString &post_id)
{
    QString query = "insert into fc_post(user_id,post_id) value ('"+user_id+"','"+post_id+"')";
    return db->insert(query);
}

