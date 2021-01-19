#ifndef MEMENTSCOENTER_H
#define MEMENTSCOENTER_H

#include "fc_observer.h"
#include <QString>

struct dynamic
{
    QString userId;
    QString headpath;
    QString nickname;
    QString con_text;
    QString con_image;//path
    int time;
};
class Subject
{
public:
    virtual void registerObserver(Observer *o) = 0;  //注册一个观察者
    virtual void removeObserver(Observer *o) = 0;     //移除一个观察者
    virtual void notifyObservers()=0;   //当状态改变时更新所以观察者
    virtual void setContent(const std::string& content)=0;
    virtual void clearObserver()=0;
};


#endif // MEMENTSCOENTER_H
