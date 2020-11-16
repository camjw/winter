#include "entity_manager.h"
#include "entity.h"
#include <utils/uuid.h>

EntityManager::EntityManager(const std::string& scene_name)
{
    root_entity = new Entity(scene_name);
    root_entity->start();
}

EntityManager::~EntityManager()
{
    printf("ENTITY MANAGER BEING DELETED\n");
    delete root_entity;
}

std::shared_ptr<Entity> EntityManager::create_entity()
{
    std::shared_ptr<Entity> new_entity = std::make_shared<Entity>(uuid::new_uuid());
    new_entity->transform->set_parent(root_entity->transform);
    new_entities.push_back(new_entity);
    return new_entity;
}

std::shared_ptr<Entity> EntityManager::create_entity(const std::string& name)
{
    std::shared_ptr<Entity> new_entity = std::make_shared<Entity>(name);
    printf("New entity name: %s\n", new_entity->name().c_str());
    printf("Transform owner name %s\n", new_entity->transform->entity()->name().c_str());
    new_entity->transform->set_parent(root_entity->transform);
    printf("New entity name: %s\n", new_entity->name().c_str());
    new_entities.push_back(new_entity);
    return new_entity;
}

std::shared_ptr<Entity> EntityManager::create_entity(std::shared_ptr<Transform> parent_transform)
{
    std::shared_ptr<Entity> new_entity = std::make_shared<Entity>(uuid::new_uuid());
    new_entity->transform->set_parent(parent_transform);
    new_entities.push_back(new_entity);
    return new_entity;
}

std::shared_ptr<Entity> EntityManager::create_entity(const std::string& name, std::shared_ptr<Transform> parent_transform)
{
    std::shared_ptr<Entity> new_entity = std::make_shared<Entity>(name);
    new_entity->transform->set_parent(parent_transform);
    new_entities.push_back(new_entity);
    return new_entity;
}

void EntityManager::update(const Time& time)
{
    for (auto& entity : entities)
    {
        entity->update(time);
    }
}

void EntityManager::late_update(const Time& time)
{
    for (auto& entity : entities)
    {
        entity->late_update(time);
    }
}

void EntityManager::process_new_entities()
{
}

const Entity* EntityManager::get_root() const
{
    return root_entity;
}
