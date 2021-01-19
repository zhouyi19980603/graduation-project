#include "qabstractlistmodel.h"


FC_FrMsg_Model::FC_FrMsg_Model(QObject *parent)
    :QAbstractListModel(parent)
{
    frmsg msg1;
    msg1.m_header="heading1";
    msg1.m_nick = "hello";
    msg1.m_mark="";
    msg1.m_message = "message1";
    frmsg msg2;
    msg2.m_header="heading3";
    msg2.m_nick = "hello3";
    msg2.m_mark="";
    msg2.m_message = "message3";
    frmsg msg3;
    msg3.m_header="heading3";
    msg3.m_nick = "hello3";
    msg3.m_mark="";
    msg3.m_message = "message3";

    _vec.push_back(msg1);
    _vec.push_back(msg2);
    _vec.push_back(msg3);
}

FC_FrMsg_Model::~FC_FrMsg_Model()
{

}

void FC_FrMsg_Model::addmodel()
{
//    frmsg msg1;
//    msg1.m_header="heading1";
//    msg1.m_nick = "hello";
//    msg1.m_mark="";
//    msg1.m_message = "message1";
//    frmsg msg2;
//    msg2.m_header="heading3";
//    msg2.m_nick = "hello3";
//    msg2.m_mark="";
//    msg2.m_message = "message3";
//    frmsg msg3;
//    msg3.m_header="heading3";
//    msg3.m_nick = "hello3";
//    msg3.m_mark="";
//    msg3.m_message = "message3";

//    _vec.push_back(msg1);
//    _vec.push_back(msg2);
//    _vec.push_back(msg3);
}

QVariant FC_FrMsg_Model::data(const QModelIndex &index, int role) const
{
    if(index.row() <0 || index.row() >= _vec.size())
    {
        return QVariant();
    }
    if(role == 0) //判断当前1所属于的状态
        return this->_vec.at(index.row()).m_header;
    else if(role == 1)
        return this->_vec.at(index.row()).m_nick;
    else if(role == 2)
        return this->_vec.at(index.row()).m_mark;
    else if(role == 3)
        return this->_vec.at(index.row()).m_message;
}

int FC_FrMsg_Model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->_vec.size();
}

QHash<int, QByteArray> FC_FrMsg_Model::roleNames() const
{
    QHash<int,QByteArray> _hash;
    _hash[0] = "heading";
    _hash[1] = "nick";
    _hash[2] = "mark";
    _hash[3] = "message";
    return _hash;
}
