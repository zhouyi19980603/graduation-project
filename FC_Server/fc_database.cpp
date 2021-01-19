#include "fc_database.h"


#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>


FC_DataBase::~FC_DataBase()
{
    db.close();
}

FC_DataBase::FC_DataBase()
{
    createConnect();
}

bool FC_DataBase::createConnect()
{

    //连接数据库
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("FC_IM");
    db.setUserName("root");
    db.setPassword("root");

    if(!db.open())
    {
//        QMessageBox::critical(0,QObject::tr("后台数据库连接失败"),"无法创建连接！请重新排查故障后重启程序.",QMessageBox::Cancel);
        qDebug()<<"failed";
        return false;
    }else {
        qDebug()<<"succed";
        return true;
    }
}

bool FC_DataBase::isQueryExist(const QString &sql)
{
    QSqlQuery query;
    if(query.exec(sql))
    {
        qDebug()<<"exist";
        return true;
    }
    else
        return false;
}
//将查询结果存储在json文件中即可

//返回读取到的sql信息，在单独的实体数据库代管类中，再去进行相应的调用

QSqlQuery FC_DataBase::query(const QString &sql)
{
    QSqlQuery query;
    query.exec(sql);
    qDebug() << "query size "<<query.size();
    return  query;

}

bool FC_DataBase::insert(const QString &user_id, const QString &friend_id)
{
    QSqlQuery query;
    query.prepare("insert into friends_info(user_id,friend_id,group_name,markname) values (?,?,?,?)");
    query.addBindValue(user_id);
    query.addBindValue(friend_id);
    query.addBindValue("friends");
    query.addBindValue("");
    query.exec();
    query.addBindValue(friend_id);
    query.addBindValue(user_id);
    query.addBindValue("friends");
    query.addBindValue("");
    query.exec();
    return true;
}

bool FC_DataBase::insert(const QString &sql)
{
    QSqlQuery query;
    if(query.exec(sql))
    {
        qDebug()<<"insert";
        return true;
    }
    else
        return false;
}

bool FC_DataBase::move(const QString &sql)
{
    QSqlQuery query;
    if(query.exec(sql))
    {
        qDebug()<<"move";
        return true;
    }
    else
        return false;
}

bool FC_DataBase::update(const QString &sql)
{
    QSqlQuery query;
    if(query.exec(sql))
    {
        qDebug()<<"update";
        return true;
    }
    else
        return false;
}

