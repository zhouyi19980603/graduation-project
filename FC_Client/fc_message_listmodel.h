#ifndef FC_MESSAGE_LISTMODEL_H
#define FC_MESSAGE_LISTMODEL_H

#include <QAbstractListModel>
#include<iostream>

class FC_Message_Instance;
class FC_Client;
class FC_instance_handle;
class FC_Chat_ListModel;
class ProfileMsg;


typedef QHash<QString, QVector<QVector<QString>>> MsgVector;

class FC_Message_ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    FC_Message_ListModel(FC_Client*client,FC_Chat_ListModel* chat_list_model,ProfileMsg* profile, QObject* parent=nullptr);
    ~FC_Message_ListModel();

    MsgVector::iterator handle_recv_msg(QVector<QString> content);
    MsgVector::iterator handle_own_msg(QVector<QString> content);
    void handle_history(QVector<QString> mess);

    //     MsgVector::iterator handle_recv_group_msg(QVector<QString> content);
    //     MsgVector::iterator handle_own_group_msg(QVector<QString> content);
    void add_msg_to_socket(QVector<QString> content);
    QString get_head_path(QString id);

    //override function
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //index and role data
    int rowCount(const QModelIndex &parent = QModelIndex()) const; //row count

    QHash<int, QByteArray> roleNames() const;

    Q_PROPERTY(QString currentChatId READ currentChatId WRITE set_currentChatId)
    Q_PROPERTY(bool msgOpacity READ msgOpacity WRITE set_msgOpacity)

    QString currentChatId() const;
    bool msgOpacity() const;
    bool set_msgOpacity(bool tmp);

    Q_INVOKABLE void send_file(const QString& acc,const QString& filename);
    Q_INVOKABLE void open_file(const QString& filename);
    Q_INVOKABLE void add(QVector<QString> mess);// display to socket
    Q_INVOKABLE void recv(QVector<QString> content);// socket to display
    Q_INVOKABLE void recv_group(QVector<QString> content);// socket to display

    Q_INVOKABLE void loadMsg(QString key);// 当打开一个chatPage时,刷新消息


    Q_INVOKABLE void set_currentChatId(QString id);


signals:
    void recv_mess();


private:
    bool _is_history=true;
    FC_Client* _client = nullptr;
    FC_Message_Instance* _instace = nullptr;
    ProfileMsg* _profile;
    FC_Chat_ListModel* _chat_listModel;
    MsgVector _all_mess;   //存储所有的消息 <消息发送者id,对行id的所有消息>
    QString _currentChatId;  //当前聊天对象Id
    QString _m_id;
    bool _msgOpacity;           //设置消息的左右显示,0表示右边显示,1表示左边显示


};

#endif // FC_MESSAGE_LISTMODEL_H
