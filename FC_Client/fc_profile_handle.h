#ifndef FC_PROFILE_HANDLE_H
#define FC_PROFILE_HANDLE_H

/**************************************************************

  @brief....: 个人信息管理模块的控制类
  @author...: zhouyi
  @date.....:2020-06-08

  ************************************************************/

#include <QObject>
#include "fc_profile.h"
#include <QString>


class FC_Client;
class FC_Profile : public QObject
{
  Q_OBJECT
public:
    FC_Profile(QObject* parent = nullptr);
    FC_Profile(FC_Client* client, QObject *parent = nullptr);
    ~FC_Profile();
    QString getAccount()const;
    Q_INVOKABLE void sendsignal();
    Q_INVOKABLE void login(const QString& acc,const QString& pass);
    Q_INVOKABLE void updateNick(const QString& acc);
    Q_INVOKABLE void updateGender(const QString& sex);
    Q_INVOKABLE void updateHeading(const QString& filepath);
    Q_INVOKABLE void registers(const QString& acc, const QString& pass);



    void update_nick(const QString& nick);
    void update_gender(const QString& sex);
    void update_heading(const char* msg);
    void handle_login(const char* msg);
    void handle_reguster(const char* msg);

    void parser_json(const std::string& content);
signals:
    void selfMessage(const QString& acc,const QString& nick,const QString& sex);
private:
    FC_Client* _client;
    ProfileMsg* _profile;
    QString _account;
};
#endif // FC_PROFILE_H
