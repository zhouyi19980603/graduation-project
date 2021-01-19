#include "fc_buddymodel.h"
#include "fc_buddyitem.h"
#include <QString>

BuddyModel* BuddyModel::instance = nullptr;

BuddyModel::BuddyModel(QObject *parent)
    :QObject(parent)
{
}


BuddyModel *BuddyModel::getInstance()
{
        if(instance == nullptr)
            instance = new BuddyModel ();
        return instance;
}

QQmlListProperty<BuddyTeam> BuddyModel::teams()
{
    return {this,this,
    &BuddyModel::appendTeam,
    &BuddyModel::teamCount,
    &BuddyModel::team,
    BuddyModel::clearTeams};
}

void BuddyModel::appendTeam(BuddyTeam *p)
{
    m_teams.append(p);
}

int BuddyModel::teamCount() const
{
    return m_teams.count();
}

BuddyTeam *BuddyModel::team(int index) const
{
    return m_teams.at(index);
}


void BuddyModel::clearTeams()
{
    m_teams.clear();
}

QVector<BuddyTeam *> &BuddyModel::get_teams()
{
    return m_teams;
}

void BuddyModel::appendTeam(QQmlListProperty<BuddyTeam> *list, BuddyTeam *p)
{
    reinterpret_cast<BuddyModel*>(list->data)->appendTeam(p);
}

int BuddyModel::teamCount(QQmlListProperty<BuddyTeam> *list)
{
    return reinterpret_cast<BuddyModel*>(list->data)->teamCount();
}

BuddyTeam *BuddyModel::team(QQmlListProperty<BuddyTeam> *list, int p)
{
    return reinterpret_cast<BuddyModel*>(list->data)->team(p);
}

void BuddyModel::clearTeams(QQmlListProperty<BuddyTeam> * list)
{
    reinterpret_cast<BuddyModel*>(list->data)->clearTeams();
}

