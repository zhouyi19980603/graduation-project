
#ifndef FC_DB_PROXY_H
#define FC_DB_PROXY_H

#include <QString>
#include <QObject>
#include <QSqlQuery>
class FC_DataBase;


/**************************************************************

  @brief....:  数据代管理者
  @author...: zhouyi
  @date.....:2020-06-10

  ************************************************************/

class FC_Server;

class DbBroker
{
public:
    DbBroker(FC_Server* server = nullptr);
    ~DbBroker();
    bool queryIsNotExist(const QString& sql);
    QSqlQuery get_user_account();
    QSqlQuery get_user_msg(const QString& account);
    QSqlQuery get_friends_list();
    QSqlQuery self_query(const QString& ery);
    QSqlQuery get_friends_list(const QString& account);
    bool update_nick(const QString& acc,const QString& nick);
    bool update_gender(const QString& acc,const QString& sex);
    bool update_mark(const QString& user_id,const QString& friend_id,const QString& mark);
    bool delete_friends(const QString& user_id,const QString& friend_id);
    bool add_friends(const QString& user_id,const QString& friends_id);
    bool serach_friend(const QString& account);
    bool add_user(const QString&,const QString&,const QString& acc);
    bool add_post(const QString& user_id,const QString& post_id);
private:
    FC_Server* _server;
    FC_DataBase* db;
};

#endif // FC_DB_PROXY_H
