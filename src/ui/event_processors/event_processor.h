#ifndef WINTER_EVENT_PROCESSOR_H
#define WINTER_EVENT_PROCESSOR_H

#include <ui/event.h>

class EventProcessor
{
public:
    virtual void process_event(const Event* event) = 0;
};

#endif // WINTER_EVENT_PROCESSOR_H
