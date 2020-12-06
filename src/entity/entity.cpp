#include "entity.h"
#include "transform.h"

Entity::Entity(std::string name)
    : _name(std::move(name))
    , transform(add_component<Transform>())

{
}

void Entity::awake()
{
    for (int i = 0; i < components.size(); i++)
    {
        components[i]->awake();
    }
}

void Entity::start()
{
    for (int i = 0; i < components.size(); i++)
    {
        components[i]->start();
    }
}

void Entity::update(const Time& time, const Input* input)
{
    for (int i = 0; i < components.size(); i++)
    {
        components[i]->update(time, input);
    }
}

void Entity::late_update(const Time& time, const Input* input)
{
    for (int i = 0; i < components.size(); i++)
    {
        components[i]->late_update(time, input);
    }
}