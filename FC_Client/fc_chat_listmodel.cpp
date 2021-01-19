#include "fc_chat_listmodel.h"

#include <QDebug>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs =std::filesystem ;


FC_Chat_ListModel::FC_Chat_ListModel(QObject *parent) : QAbstractListModel(parent)
{
    int i = Qt::DisplayRole;
    this->_roles.insert(i++,"userName");
    this->_roles.insert(i++,"lastContent");
    this->_roles.insert(i++,"imagePath");

}

QVariant FC_Chat_ListModel::data(const QModelIndex &index, int role) const
{

    if(index.row() <0 || index.row() >= _data.size())
    {
        return QVariant();
    }
    if(role == 0) //判断当前1所属于的状态
        return this->_data.at(index.row()).at(0);
    else if(role == 1)
        return this->_data.at(index.row()).at(1);
    else if(role == 2)
        return this->_data.at(index.row()).at(2);
    return this->_data.at(index.row()).at(role);
}

int FC_Chat_ListModel::rowCount(const QModelIndex &) const
{
    return this->_data.size();//函数返回模型中的项目总数
}

QHash<int, QByteArray> FC_Chat_ListModel::roleNames() const
{
    return this->_roles;
}


void FC_Chat_ListModel::add(){
    beginRemoveRows(QModelIndex(),0,rowCount());
    this->_data.clear();
    endRemoveRows();
    emit update_mess();
    QVector<QVector<QString>>temp (_data);

    LastMsgVector::iterator iter =this->_all_last_msg.find(this->_one_last_msg.at(0));  //检索key
    if(iter == this->_all_last_msg.end()){
        _all_last_msg.insert(this->_one_last_msg.at(0),this->get_last_msg());
    }else {
        iter.value() =this->get_last_msg();
    }

    LastMsgVector::iterator tmpIter = this->_all_last_msg.begin();
    while(tmpIter != this->_all_last_msg.end()){
        beginInsertRows(QModelIndex(),rowCount(),rowCount());
        //消息直接在UI上打印
        this->_data.push_back(tmpIter.value());
        endInsertRows();
        emit update_mess();
        ++tmpIter;
    }
}

QVector<QString> FC_Chat_ListModel::get_last_msg()
{
    return this->_one_last_msg;
}

void FC_Chat_ListModel::set_last_msg(QVector<QString> msg)
{
    this->_one_last_msg = msg;
}
