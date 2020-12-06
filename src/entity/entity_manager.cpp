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
    printf("Entity manager deleted for scene %s\n", root_entity->name().c_str());
    delete root_entity;
}

std::shared_ptr<Entity> EntityManager::create_entity()
{
    std::shared_ptr<Entity> new_entity = std::make_shared<Entity>(uuid::new_uuid());
    new_entity->transform->set_parent(root_entity->transform);
    new_entities.push(new_entity);
    return new_entity;
}

std::shared_ptr<Entity> EntityManager::create_entity(const std::string& name)
{
    std::shared_ptr<Entity> new_entity = std::make_shared<Entity>(name);
    new_entity->transform->set_parent(root_entity->transform);
    new_entities.push(new_entity);
    return new_entity;
}

std::shared_ptr<Entity> EntityManager::create_entity(std::shared_ptr<Transform> parent_transform)
{
    std::shared_ptr<Entity> new_entity = std::make_shared<Entity>(uuid::new_uuid());
    new_entity->transform->set_parent(parent_transform);
    new_entities.push(new_entity);
    return new_entity;
}

std::shared_ptr<Entity> EntityManager::create_entity(const std::string& name, std::shared_ptr<Transform> parent_transform)
{
    std::shared_ptr<Entity> new_entity = std::make_shared<Entity>(name);
    new_entity->transform->set_parent(parent_transform);
    new_entities.push(new_entity);
    return new_entity;
}

void EntityManager::update(const Time& time, const Input* input)
{
    for (auto& entity : entities)
    {
        entity->update(time, input);
    }
}

void EntityManager::late_update(const Time& time, const Input* input)
{
    for (auto& entity : entities)
    {
        entity->late_update(time, input);
    }
}

void EntityManager::process_new_entities()
{
    while (!new_entities.empty())
    {
        std::shared_ptr<Entity> new_entity = new_entities.front();
        new_entity->start();
        entities.push_back(new_entity);

        new_entities.pop();
    }
}

const Entity* EntityManager::get_root() const
{
    return root_entity;
}
