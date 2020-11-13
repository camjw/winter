#ifndef WINTER_ACTION_H
#define WINTER_ACTION_H

#include <memory>

template <class T>
class Action
{
public:
    virtual void run(std::shared_ptr<T> entity) = 0;
};

#endif // WINTER_ACTION_H
