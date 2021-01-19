#ifndef FC_STATUS_H
#define FC_STATUS_H


#include <QObject>
#include <QString>

class FC_MessageStatus : public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString acc READ acc WRITE setAcc NOTIFY accChanged)
public:
    static FC_MessageStatus* getInstance();
//    FC_MessageStatus(QObject* parent = nullptr);
    enum Status{
      LoginSucc, // 登录成功
      LoginError, //登录失败
      RegisterSucc //注册成功
    };
    Status status() const;
    QString acc() const;

    void setStatus(Status va);
    void setAcc(const QString& acc);
signals:
    void statusChanged();
    void accChanged();
private:
    static FC_MessageStatus* instance;
    FC_MessageStatus(QObject* parent = nullptr);
    Status m_status;
    QString m_acc;
};

#endif // FC_STATUS_H
