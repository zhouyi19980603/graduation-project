#include "fc_moments_listmodel.h"
#include <iostream>

FC_Moments_Model::FC_Moments_Model(QObject *parent)
    :QAbstractListModel(parent)
{
}

FC_Moments_Model *FC_Moments_Model::getInstance()
{
    static FC_Moments_Model instance;
    return &instance;
}

QVariant FC_Moments_Model::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= _data.size())
        return QVariant();
    if(role == 0)
        return this->_data.at(index.row()).headpath;
    else if(role == 1)
        return this->_data.at(index.row()).nickname;
    else if(role == 2)
        return this->_data.at(index.row()).con_text;
    else if(role == 3)
        return this->_data.at(index.row()).con_image;
    else if(role == 4)
        return this->_data.at(index.row()).time;
    else if(role == 5)
        return this->_data.at(index.row()).userId;
    else if(role == 6)
        return this->_data.at(index.row()).dyId;
    else if (role == 7) {
        return this->_data.at(index.row()).like_text;
    }
    else if (role == 8) {
//        return  this->_data.at(index.row()).comments;
    }
    else if(role == 9){
        return this->_data.at(index.row()).is_like;
    }
    else if (role == 10) {
        return  this->_data.at(index.row()).commentsNum;
    }
    return QVariant();
}

int FC_Moments_Model::rowCount(const QModelIndex &parent) const
{
    return _data.size();
}

QHash<int, QByteArray> FC_Moments_Model::roleNames() const
{
    QHash<int,QByteArray> _roles;
    _roles[0] = "heading";
    _roles[1] = "nickname";
    _roles[2] = "content_text";
    _roles[3] = "content_image";
    _roles[4] = "time";
    _roles[5] = "userid";
    _roles[6] = "dyId";
    _roles[7] = "like_text";
    _roles[8] = "comments";
    _roles[9] = "is_like";
    _roles[10] = "comNum";
    return _roles;
}

void FC_Moments_Model::clear()
{
    beginRemoveRows(QModelIndex(),0,rowCount()-1);
    _data.erase(_data.begin(),_data.end());
    endRemoveRows();
}

void FC_Moments_Model::update_model(const QString &dyId, const QString &content)
{
    int index = getIndex(dyId);
    _data[index].is_like = !_data[index].is_like;
//    _data[index].like_text += content;
    emit update_mess();
}

int FC_Moments_Model::getIndex(const QString &dyId)
{
    int index = 0;
    for(int i=0;i < _data.size();i++)
    {
        if(this->_data[i].dyId == dyId)
        {
            index = i;break;
        }
    }
    return index;
}

void FC_Moments_Model::add(dynamic& nic)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
//    beginInsertRows(QModelIndex(),0,0);
//    std::cout<<"进来了"<<std::endl;
    this->_data.push_back(nic);
//    this->_data.insert(0,nic);
    endInsertRows();
}

void FC_Moments_Model::add()
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    std::cout<<"进来了"<<std::endl;
    dynamic one;
    one.headpath = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/@13456.jpg";
    one.nickname = "张礼";
    one.con_text = "夜阑卧听风吹雨。";
    one.con_image = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/one.jpg";
    this->_data.push_back(one);
    endInsertRows();
    emit update_mess();
}
