#include "fc_comments_listmodel.h"
#include <json/json.h>
#include <fstream>
#include <iostream>

CommentsModel *CommentsModel::getInstance()
{
    static CommentsModel instance;
    return &instance;
}

CommentsModel::CommentsModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

QVariant CommentsModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= _data.size())
        return QVariant();
    if(role == 0)
        return this->_data.at(index.row()).id;
    else if(role == 1)
        return this->_data.at(index.row()).post_id;
    else if(role == 2)
        return this->_data.at(index.row()).content;
    else if(role == 3)
        return this->_data.at(index.row()).user_id;
    else if(role == 4)
        return this->_data.at(index.row()).parent_id;
    else if(role == 5)
        return this->_data.at(index.row()).time;
    else if(role == 6)
        return this->_data.at(index.row()).name;
    return QVariant();
}

int CommentsModel::rowCount(const QModelIndex &parent) const
{
    return _data.size();
}

QHash<int, QByteArray> CommentsModel::roleNames() const
{
    QHash<int,QByteArray> _roles;
    _roles[0] = "id";
    _roles[1] = "post_d";
    _roles[2] = "content";
    _roles[3] = "user_id";
    _roles[4] = "parent_id";
    _roles[5] = "time";
    _roles[6] = "name";
    return  _roles;
}

//void CommentsModel::parsing()
//{
//    //从json文件中读取，并获得是添加在那个项中
//    Json::Value root;
//    Json::Reader reader;
//    std::ifstream is;

//    is.open("./config/comments.json",std::ios::binary);
//    if(reader.parse(is,root,false))
//    {
//        //解析到json文件,获得评论表
//        Json::Value ids = root["ids"];
//        for(int i=0;i<ids.size();i++)
//        {
//            Comment com;
//            //从"comments"中获取对应的ids
//            std::string id = ids[i].asString();
//            Json::Value item = root["comments"][id]; //得到对应的评论数据
//            com.id = QString::fromLocal8Bit(item["id"].asCString());
//            com.content = QString::fromLocal8Bit(item["content"].asCString());
//            com.parent_id = QString::fromLocal8Bit(item["parent_id"].asCString());
//            com.name =QString::fromLocal8Bit(item["user_id"].asCString());
//            if(item["parent_id"] == "")
//            {
//                //表明这是一级评论
//                beginInsertRows(QModelIndex(),rowCount(),rowCount());
//                this->_data.push_back(com);
//                endInsertRows();
//            }else
//            {
//                //表明父_id有值，这是一个回复,找到父_id所在的位置
//                int index =0;
//                for(int j=0;j<this->_data.size();j++)
//                {
//                    Comment each = _data[j];
//                    if(each.id.toStdString() == item["parent_id"].asString())
//                    {
////                        //找到父亲所在的项
//                        index = j+1;
//                        for(int jj=j+1;jj<this->_data.size();jj++)
//                        {
//                            if(_data[jj].parent_id.toStdString() != item["parent_id"].asString()){
//                                index = jj;
//                                break;
//                            }
//                        }
//                        break;
//                    }
//                }
//                beginInsertRows(QModelIndex(),index,index);
//                this->_data.insert(index,com);
//                endInsertRows();
//            }
//        }
//    }else
//    {
//        std::cout<<"解析失败"<<std::endl;
//        exit(0);
//    }
//}

void CommentsModel::clear()
{
    _data.clear();
}

int CommentsModel::getIndex(const std::string &parent_id)
{
    int index =0;
    for(int j=0;j<this->_data.size();j++)
    {
        Comment each = _data[j];
        if(each.id.toStdString() == parent_id)
        {
//                        //找到父亲所在的项
            index = j+1;
            for(int jj=j+1;jj<this->_data.size();jj++)
            {
                if(_data[jj].parent_id.toStdString() != parent_id){
                    index = jj;
                    break;
                }
            }
            break;
        }
    }
    return index;
}

void CommentsModel::add(Comment &cm, int index)
{
    beginInsertRows(QModelIndex(),index,index);
    this->_data.insert(index,cm);
    endInsertRows();
}


//bool CommentsModel::insertRows(int row, int count, const QModelIndex &parent)
//{
//    beginInsertRows(parent,row,row);
//    endInsertRows();
//}
