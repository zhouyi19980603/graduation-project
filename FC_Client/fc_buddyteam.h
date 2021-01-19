#ifndef FC_BUDDYTEAM_H
#define FC_BUDDYTEAM_H
/**************************************************************

  @brief....:C++端的数据，当作QML端的model
  @author...: zhouyi
  @date.....:2020-05-23

  ************************************************************/

#include <QObject>
#include <QQmlListProperty>

class BuddyItem;

class BuddyTeam : public QObject
{
  Q_OBJECT
//    Q_PROPERTY(QQmlListProperty<BuddyItem> buddys READ buddys NOTIFY buddysChanged)
//    Q_PROPERTY(QString teamname READ teamname WRITE setTeamname NOTIFY teamChanged)

    Q_PROPERTY(QQmlListProperty<BuddyItem> buddys READ buddys)
    Q_PROPERTY(QString teamname READ teamname WRITE setTeamname)
    Q_PROPERTY(int teamId READ teamId WRITE setTeamId)
public:
    BuddyTeam(QObject* parent = nullptr);

    QQmlListProperty<BuddyItem> buddys();
    void appendItem(BuddyItem*);
    int itemCount() const;
    BuddyItem *item(int)const;
    void clearItems();
    QVector<BuddyItem *>& get_items();


    QString teamname()const;
    int teamId() const;

    void setTeamname(const QString& str);
    void setTeamId(const int& id);
signals:
//    void teamChanged();
//    void buddysChanged();
private:


    static void appendItem(QQmlListProperty<BuddyItem>*,BuddyItem*);
    static int itemCount(QQmlListProperty<BuddyItem>*);
    static BuddyItem* item(QQmlListProperty<BuddyItem>*,int);
    static void clearItems(QQmlListProperty<BuddyItem>*);

    QString m_teamname;
    int m_id;
    QVector<BuddyItem *>m_items;

};

#endif // FC_BUDDYTEAM_H
