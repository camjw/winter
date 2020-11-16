#ifndef WINTER_COMPONENT_H
#define WINTER_COMPONENT_H

#include <timer.h>

class Transform;
class Entity;
class Component
{
public:
    Component(Entity* entity);
    virtual ~Component() {}

    virtual void start() { }
    virtual void awake() { }
    virtual void update(const Time& time) { }
    virtual void late_update(const Time& time) { }

    void set_enabled(bool is_enabled)
    {
        if (!this->is_enabled && is_enabled)
        {
            awake();
        }

        this->is_enabled = is_enabled;
    }

    std::shared_ptr<Transform> transform() const;

    Entity* entity() const;

protected:
    bool is_enabled;
    Entity* _entity;
};

#endif // WINTER_COMPONENT_H
