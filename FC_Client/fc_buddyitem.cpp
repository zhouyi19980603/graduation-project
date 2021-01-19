#include "fc_buddyitem.h"

BuddyItem::BuddyItem(QObject *parent)
    :QObject(parent)
{

}

QString BuddyItem::account() const
{
    return m_account;
}

QString BuddyItem::nickname() const
{
    return m_nickname;
}

QString BuddyItem::heading() const
{
    return m_heading;
}

QString BuddyItem::gender() const
{
    return m_gender;
}

QString BuddyItem::sign() const
{
    return m_sign;
}

QString BuddyItem::markname() const
{
    return m_markname;
}

int BuddyItem::itemId() const
{
    return m_id;
}

void BuddyItem::setAccount(const QString &str)
{
    m_account = str;
//    emit dataChanged();
}

void BuddyItem::setNickname(const QString &str)
{
    m_nickname = str;
    //    emit nicknameChanged();
}

void BuddyItem::setHeading(const QString &str)
{
    m_heading = str;
}

void BuddyItem::setGender(const QString &str)
{
    m_gender = str;
}

void BuddyItem::setSign(const QString &str)
{
    m_sign = str;
}

void BuddyItem::setMarkname(const QString &str)
{
    m_markname = str;
}

void BuddyItem::setItemId(const int &id)
{
    m_id = id;
}
