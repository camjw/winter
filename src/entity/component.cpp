#include "component.h"
#include "entity.h"

Component::Component(Entity* entity)
    : _entity(entity)
{
}

std::shared_ptr<Transform> Component::transform() const
{
    return _entity->transform;
}

Entity* Component::entity() const
{
    return _entity;
}