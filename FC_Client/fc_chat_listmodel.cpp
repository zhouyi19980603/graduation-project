#include "fc_chat_listmodel.h"

#include <QDebug>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs =std::filesystem ;


FC_Chat_ListModel::FC_Chat_ListModel(QObject *parent) : QAbstractListModel(parent)
{
}

QVariant FC_Chat_ListModel::data(const QModelIndex &index, int role) const
{

    if(index.row() <0 || index.row() >= _data.size())
    {
        return QVariant();
    }
    if(role == 0) //判断当前1所属于的状态
        return this->_data.at(index.row()).account;
    else if(role == 1)
        return this->_data.at(index.row()).content;
    else if(role == 2)
        return this->_data.at(index.row()).heading;
    else if(role == 3)
        return this->_data.at(index.row()).name;
    else if(role == 4)
        return this->_data.at(index.row()).time;
    return QVariant();
}

int FC_Chat_ListModel::rowCount(const QModelIndex &) const
{
    return this->_data.size();//函数返回模型中的项目总数
}

QHash<int, QByteArray> FC_Chat_ListModel::roleNames() const
{
    QHash<int,QByteArray> _roles;
    _roles[0] = "account";
    _roles[1] = "content";
    _roles[2] = "heading";
    _roles[3] = "name";
    _roles[4] = "time";
    return _roles;
}

void FC_Chat_ListModel::add(QVector<QString> item)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    LastMsg msg;
    msg.account = item.at(0);
    msg.content = item.at(1);
    msg.heading = item.at(2);
    msg.name = item.at(3);
    msg.time = item.at(4);

    auto value = _hash.find(item.at(0));
    if(value == _hash.end())
    {
        //表明没有找到
        _hash[item.at(0)] = _data.size();
        _data.push_back(msg);
    }else
    {
        int index = _hash[item.at(0)];
        _data[index] = msg;
    }
    endInsertRows();
}


//void FC_Chat_ListModel::add(){
//    beginRemoveRows(QModelIndex(),0,rowCount());
//    this->_data.clear();
//    endRemoveRows();
//    emit update_mess();
//    QVector<QVector<QString>>temp (_data);

//    LastMsgVector::iterator iter =this->_all_last_msg.find(this->_one_last_msg.at(0));  //检索key
//    if(iter == this->_all_last_msg.end()){
//        _all_last_msg.insert(this->_one_last_msg.at(0),this->get_last_msg());
//    }else {
//        iter.value() =this->get_last_msg();
//    }

//    LastMsgVector::iterator tmpIter = this->_all_last_msg.begin();
//    while(tmpIter != this->_all_last_msg.end()){
//        beginInsertRows(QModelIndex(),rowCount(),rowCount());
//        //消息直接在UI上打印
//        this->_data.push_back(tmpIter.value());
//        endInsertRows();
//        emit update_mess();
//        ++tmpIter;
//    }
//}

//QVector<QString> FC_Chat_ListModel::get_last_msg()
//{
//    return this->_one_last_msg;
//}

//void FC_Chat_ListModel::set_last_msg(QVector<QString> msg)
//{
//    this->_one_last_msg = msg;
//}
