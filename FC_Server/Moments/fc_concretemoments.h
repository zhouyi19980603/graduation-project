#ifndef CONCRETEMOMENTS_H
#define CONCRETEMOMENTS_H

#include "fc_subject.h"
#include <vector>


class ConcreteMoments : public Subject
{
public:
    void registerObserver(Observer *o) override;
    void notifyObservers() override;
    void removeObserver(Observer *o) override;
    void setContent(const std::string& content,unsigned type) override;
    void clearObserver() override;
private:
    std::vector<Observer*> _observers; //参观者集合
    std::string _content;
    unsigned _type;
};

#endif // CONCRETEMOMENTS_H
