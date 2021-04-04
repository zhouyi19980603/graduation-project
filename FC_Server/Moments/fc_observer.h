#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class Observer
{
public:
    virtual void update(const std::string& content,unsigned type) =0;
};

#endif // OBSERVER_H
