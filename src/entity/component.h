#ifndef WINTER_COMPONENT_H
#define WINTER_COMPONENT_H

#include "entity.h"

class Transform;
class Component
{
public:
    Component(Entity* entity): _entity(entity) {}

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

    Transform* transform()
    {
        return _entity->transform.get();
    }

    const Entity* entity() const
    {
        return _entity;
    }

private:
    Entity* _entity;

    bool is_enabled;
};

#endif // WINTER_COMPONENT_H
