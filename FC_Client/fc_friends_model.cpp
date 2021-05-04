#include "fc_friends_model.h"

FMsgModel *FMsgModel::getInstance()
{
    static FMsgModel instance;
    return &instance;
}

QVariant FMsgModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= _data.size())
        return QVariant();
    if(role == 0)
        return this->_data.at(index.row()).account;
    else if(role == 1)
        return this->_data.at(index.row()).heading;
    else if(role == 2)
        return this->_data.at(index.row()).content;
    else if(role == 3)
        return this->_data.at(index.row()).name;
    return QVariant();
}

int FMsgModel::rowCount(const QModelIndex &parent) const
{
    return _data.size();
}

QHash<int, QByteArray> FMsgModel::roleNames() const
{
    QHash<int,QByteArray> _roles;
    _roles[0] = "account";
    _roles[1] = "heading";
    _roles[2] = "content";
    _roles[3] = "name";
    return _roles;
}

void FMsgModel::insert(FMsg& item)
{
    beginInsertRows(QModelIndex(),0,rowCount());
    this->_data.push_back(item);
    endInsertRows();
}

FMsgModel::FMsgModel(QObject *parent)
    :QAbstractListModel(parent)
{

}
