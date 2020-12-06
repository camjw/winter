#ifndef WINTER_ENTITY_MANAGER_H
#define WINTER_ENTITY_MANAGER_H

#include "transform.h"
#include <input/input.h>
#include <memory>
#include <vector>

class Entity;
class EntityManager
{
public:
    explicit EntityManager(const std::string& scene_name);
    ~EntityManager();

    std::shared_ptr<Entity> create_entity();
    std::shared_ptr<Entity> create_entity(const std::string& name);
    std::shared_ptr<Entity> create_entity(std::shared_ptr<Transform> parent_transform);
    std::shared_ptr<Entity> create_entity(const std::string& name, std::shared_ptr<Transform> parent_transform);

    const Entity* get_root() const;

    void update(const Time& time, const Input* input);
    void late_update(const Time& time, const Input* input);

    void process_new_entities();

private:
    Entity* root_entity;
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Entity>> new_entities;
};

#endif //WINTER_ENTITY_MANAGER_H
