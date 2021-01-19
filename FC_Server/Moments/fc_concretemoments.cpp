#include "fc_concretemoments.h"
#include <algorithm>

using std::find;

void ConcreteMoments::registerObserver(Observer *o)
{
    _observers.push_back(o);
}

void ConcreteMoments::notifyObservers()
{
    for(const auto &each : _observers)
        each->update(_content);
}
//移除一个观察者
void ConcreteMoments::removeObserver(Observer *o)
{
    _observers.erase(find(_observers.begin(),_observers.end(),o));
}

void ConcreteMoments::setContent(const std::string &content)
{
    _content = content;
    notifyObservers();
}

void ConcreteMoments::clearObserver()
{
    _observers.clear();
}
