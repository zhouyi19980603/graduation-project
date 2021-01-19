#ifndef FC_BUDDYITEM_H
#define FC_BUDDYITEM_H

/**************************************************************

  @brief....:model中的每一个好友项
  @author...: zhouyi
  @date.....:2020-05-23

  ************************************************************/
#include <QObject>

class BuddyItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString account READ account WRITE setAccount)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname)
    Q_PROPERTY(int itemId READ itemId WRITE setItemId)
    Q_PROPERTY(QString heading READ heading WRITE setHeading)
    Q_PROPERTY(QString gender READ gender WRITE setGender)
    Q_PROPERTY(QString sign READ sign WRITE setSign)
    Q_PROPERTY(QString markname READ markname WRITE setMarkname)
public:
    BuddyItem(QObject* parent=nullptr);
    //getter
    QString account()const;
    QString nickname()const;
    QString heading()const;
    QString gender()const;
    QString sign()const;
    QString markname()const;
    int itemId() const;

    //setter
    void setAccount(const QString& str);
    void setNickname(const QString& str);
    void setHeading(const QString& str);
    void setGender(const QString& str);
    void setSign(const QString& str);
    void setMarkname(const QString& str);
    void setItemId(const int& id);
private:
    QString m_account;
    QString m_nickname;
    QString m_heading;
    QString m_gender;
    QString m_sign;
    QString m_markname;
    int m_id;
};

#endif // FC_BUDDYITEM_H
