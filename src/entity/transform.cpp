#include "transform.h"
#include "entity.h"

Transform::Transform(Entity* entity)
    : Component(entity)
{
}

void Transform::set_parent(std::shared_ptr<Transform> parent_transform)
{
    _parent = parent_transform;
    parent_transform->children.push_back(this);
}