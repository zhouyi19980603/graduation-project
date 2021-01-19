#ifndef FC_PROFILE_H
#define FC_PROFILE_H

#include <QObject>
#include <QString>

/**************************************************************

  @brief....:界面显示的Profile实体
  @author...: zhouyi
  @date.....:2020-06-09

  ************************************************************/

class ProfileMsg :public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString account READ account NOTIFY accountChanged)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QString heading READ heading WRITE setHeading NOTIFY headingChanged)
    Q_PROPERTY(QString sign READ sign WRITE setSign NOTIFY signChanged)
public:
    static ProfileMsg* getInstance(); //单例的设计模式


    //setter
    void setAccount(const QString& acc);
    void setNickname(const QString& nick);
    void setGender(const QString& gender);
    void setHeading(const QString& haeding);
    void setSign(const QString& sign);

    //getter
    QString account() const;
    QString nickname() const;
    QString gender() const;
    QString heading() const;
    QString sign() const;

signals:
    void accountChanged();
    void nicknameChanged();
    void genderChanged();
    void headingChanged();
    void signChanged();

private:
    static ProfileMsg* instance;
    ProfileMsg(QObject* parent = nullptr);

    QString m_account;
    QString m_nickname;
    QString m_heading; //存放的是图片的路径
    QString m_sign;
    QString m_gender;
};

#endif // FC_PROFILE_H
