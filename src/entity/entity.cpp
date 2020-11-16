#include "entity.h"
#include "transform.h"

Entity::Entity(std::string name)
    : _name(std::move(name))
    , transform(add_component<Transform>())

{
}

void Entity::awake()
{
    for (int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->awake();
    }
}

void Entity::start()
{
    for (int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->start();
    }
}

void Entity::update(const Time& time)
{
    for (int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->update(time);
    }
}

void Entity::late_update(const Time& time)
{
    for (int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->late_update(time);
    }
}