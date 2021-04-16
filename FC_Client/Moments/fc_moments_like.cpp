#include "fc_moments_like.h"

LikeMsg* LikeMsg::instance = nullptr;
LikeMsg *LikeMsg::getInstance()
{
    if(instance == nullptr)
        instance = new LikeMsg();
    return instance;
}

void LikeMsg::setLike_text(const QString &text)
{
    if(m_like_text != text)
    {
        m_like_text = text;
        emit like_textChanged();
    }else
    {
        emit like_textChanged();
    }
}

void LikeMsg::setTime(const QString &time)
{
    if(m_time != time)
    {
        m_time = time;
        emit timeChanged();
    }else
    {
        emit timeChanged();
    }
}

void LikeMsg::setIsLike(const bool &value)
{
    if(m_isLike != value )
    {
        m_isLike = value;
        emit isLikeChanged();
    }else
        emit isLikeChanged();
}

QString LikeMsg::like_text() const
{
    return m_like_text;
}

bool LikeMsg::isLike() const
{
    return m_isLike;
}

QString LikeMsg::time() const
{
    return m_time;
}

LikeMsg::LikeMsg(QObject *parent)
    :QObject(parent)
{

}
