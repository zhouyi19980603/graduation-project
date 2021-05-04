#ifndef FC_CHAT_LISTMODEL_H
#define FC_CHAT_LISTMODEL_H

/**************************************************************

  @brief....: chatViews.qml最新消息加载
  @author...: ran
  @date.....:2020-06-25

  ************************************************************/
#include <QAbstractListModel>
#include<iostream>

class FC_Message_Instance;
class FC_Client;
class FC_instance_handle;

struct LastMsg{
    QString account;
    QString content;
    QString name;
    QString heading;
    QString time;
};

//<userId,<userName,imagePaht,lastcontent>>
typedef QHash <QString, QVector<QString>> LastMsgVector;

class FC_Chat_ListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    FC_Chat_ListModel(QObject *parent = nullptr);


    //override function
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //index and role data
    int rowCount(const QModelIndex &parent = QModelIndex()) const; //row count

    QHash<int, QByteArray> roleNames() const;

    void add(QVector<QString> item);
private:
    FC_Client* _client = nullptr;
    QHash<QString,int> _hash;//记录这条命令是否出现过，出现者在原来的基础上更改
    QVector<LastMsg> _data;
};

#endif // FC_CHAT_LISTMODEL_H
