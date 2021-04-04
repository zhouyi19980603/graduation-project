#include "fc_moments_listmodel.h"
#include <iostream>

FC_Moments_Model::FC_Moments_Model(QObject *parent)
    :QAbstractListModel(parent)
{
//    dynamic one;
//    one.headpath = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/@13456.jpg";
//    one.nickname = "张礼";
//    one.con_text = "夜阑卧听风吹雨。";
//    one.con_image = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/one.jpg";
//    _data.push_back(one);
//    dynamic one1;
//    one1.headpath = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/@13456.jpg";
//    one1.nickname = "张礼";
//    one1.con_text = "夜阑卧听风吹雨。";
//    one1.con_image = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/one.jpg";
//    dynamic one2;
//    one2.headpath = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/@13456.jpg";
//    one2.nickname = "张礼";
//    one2.con_text = "夜阑卧听风吹雨。";
//    one2.con_image = "file:///run/media/root/linux_data/FC_IM/FC_Client/qml/BussinessPage/Moments/one.jpg";
//    _data.push_back(one1);
//    _data.push_back(one2);
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
    return _roles;
}

void FC_Moments_Model::add(dynamic& nic)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    std::cout<<"进来了"<<std::endl;
    this->_data.push_back(nic);
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
}
