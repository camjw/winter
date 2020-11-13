#ifndef WINTER_EVENT_H
#define WINTER_EVENT_H

class Event
{
public:
    virtual ~Event() {};
    virtual const char* get_type() const = 0;
};

#endif // WINTER_EVENT_H
