#ifndef FC_DATABASE_H
#define FC_DATABASE_H

#include <QObject>
#include <QString>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

/**************************************************************

  @brief....:核心底层数据库，基础操作，里面包含redis和mysql数据库
  @author...: zhouyi
  @date.....:2020-05-18

  ************************************************************/

#include <QObject>
#include <QString>
#include <QVector>
#include <QSqlDatabase>


class FC_DataBase
{
public:
    FC_DataBase();
    bool isQueryExist(const QString& sql); //判断sql语句是否存在数据库中
    QSqlQuery query(const QString& sql);
    bool insert(const QString& user_id,const QString& friend_id); //添加好友的底层接口
    bool insert(const QString& sql);
    bool move(const QString& sql);
    bool update(const QString& sql);
    bool createConnect();

    ~FC_DataBase();
private:
   //这里放Server总类
    QSqlDatabase db;
};

#endif // FC_DATABASE_H
