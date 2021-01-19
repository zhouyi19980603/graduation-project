#include "fc_profile.h"

ProfileMsg* ProfileMsg::instance = nullptr;

ProfileMsg *ProfileMsg::getInstance()
{
    if(instance == nullptr)
        instance = new ProfileMsg ();
    return instance;
}

void ProfileMsg::setAccount(const QString &acc)
{
    m_account = acc;
    emit accountChanged(); //必须要有信号，QML端才能即时的检测信号是否被更改
}

void ProfileMsg::setNickname(const QString &nick)
{
    m_nickname = nick;
    emit nicknameChanged();
}

void ProfileMsg::setGender(const QString &gender)
{
    if( m_gender != gender)
    {
        m_gender = gender;
        emit genderChanged();
    }
}

void ProfileMsg::setHeading(const QString &heading)
{
    if( m_heading != heading)
    {
//        m_heading = "";
        m_heading = heading;
        emit headingChanged();
    }else
    {
        emit headingChanged();
    }
}

void ProfileMsg::setSign(const QString &sign)
{
    if(m_sign != sign)
    {
        m_sign = sign;
        emit signChanged();
    }
}

QString ProfileMsg::account() const
{
    return m_account;
}

QString ProfileMsg::nickname() const
{
    return m_nickname;
}

QString ProfileMsg::gender() const
{
    return m_gender;
}

QString ProfileMsg::heading() const
{
    return  m_heading;
}

QString ProfileMsg::sign() const
{
    return m_sign;
}


ProfileMsg::ProfileMsg(QObject *parent)
    :QObject(parent)
{

}
