#include "component.h"
#include "entity.h"

Component::Component(Entity* entity)
    : _entity(entity)
{
    printf("Creating component entity name is %s\n", _entity->name().c_str());
}

std::shared_ptr<Transform> Component::transform() const
{
    return _entity->transform;
}

Entity* Component::entity() const
{
    printf("Getting entity name is %s\n", _entity->name().c_str());
    return _entity;
}