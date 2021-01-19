#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer
{
public:
    virtual void update(const std::string& content) =0;
};

#endif // OBSERVER_H
