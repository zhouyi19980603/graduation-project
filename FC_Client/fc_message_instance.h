#ifndef FC_MESSAGE_INSTANCE_H
#define FC_MESSAGE_INSTANCE_H

#include <QVariant>
#include <QVector>
class FC_Client;
class FC_Message_Instance
{
public:
    FC_Message_Instance(FC_Client* client);

    //override function
    QVariant data(const int &index, int role ) const; //index and role data
    int rowCount() const; //row count
    QHash<int, QByteArray> roleNames() const;


    //transfer function
    void add(QVector<QString> content);//display to socket
    void recv(QVector<QString> content);//socket to display

    void add_msg_to_socket(QVector<QString> content);
    void clearMsg();


private:
    QHash<int, QByteArray> _roles;//store rolename
    QVector<QVector<QString>> _data; //store message
    FC_Client* _client = nullptr;
};

#endif // FC_MESSAGE_INSTANCE_H
