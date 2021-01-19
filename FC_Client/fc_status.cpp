#include "fc_status.h"
FC_MessageStatus* FC_MessageStatus::instance = nullptr;

FC_MessageStatus *FC_MessageStatus::getInstance()
{
    if(instance == nullptr)
        instance = new FC_MessageStatus ();
    return instance;
}

FC_MessageStatus::Status FC_MessageStatus::status() const
{
    return m_status;
}

QString FC_MessageStatus::acc() const
{
    return m_acc;
}

void FC_MessageStatus::setStatus(FC_MessageStatus::Status va)
{
    m_status = va;
    emit statusChanged();
}

void FC_MessageStatus::setAcc(const QString &acc)
{
    m_acc = acc;
    emit accChanged();
}

FC_MessageStatus::FC_MessageStatus(QObject* parent)
    :QObject(parent)
{

}
