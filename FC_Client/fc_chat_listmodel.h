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

    Q_INVOKABLE void add();


//    void handle_last_msg(QVector<QString> content);

    QVector<QString> get_last_msg();
    void set_last_msg(QVector<QString>);

signals:
    void update_mess();


    //   void test_signal();
private:
    bool m_bool;
    QHash<int, QByteArray> _roles;//store rolename
    QVector<QVector<QString>> _data; //store message
    FC_Client* _client = nullptr;
    LastMsgVector _all_last_msg;
    QVector<QString> _one_last_msg;
};

#endif // FC_CHAT_LISTMODEL_H
