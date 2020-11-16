#include "transform.h"
#include "entity.h"

Transform::Transform(Entity* entity)
    : Component(entity)
{
    printf("Creating transform entity name is %s\n", _entity->name().c_str());
}

void Transform::set_parent(std::shared_ptr<Transform> parent_transform)
{
    printf("new parent entity: %s\n", parent_transform->entity()->name().c_str());
    printf("this entity name: %s\n", entity()->name().c_str());
    _parent = parent_transform;
    parent_transform->children.push_back(this);
    printf("parent entity first child : %s\n", _parent->children[0]->entity()->name().c_str());
}