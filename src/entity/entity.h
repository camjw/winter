#ifndef WINTER_ENTITY_H
#define WINTER_ENTITY_H

#include <memory>
#include <timer.h>
#include <vector>
#include "entity_manager.h"

class Transform;
class Component;
class Entity
{
public:
    friend class EntityManager;

    // WARNING: this method should only be called from the entity manager;
    Entity(std::string name);

    ~Entity()
    {
        printf("Deleting entity with name %s\n", _name.c_str());
    }

    void awake();
    void start();
    void update(const Time& time);
    void late_update(const Time& time);

    template <typename T> std::shared_ptr<T> add_component()
    {
        std::shared_ptr<T> existing_component = get_component<T>();
        if (existing_component)
        {
            return existing_component;
        }

        std::shared_ptr<T> new_component = std::make_shared<T>(this);
        components.push_back(new_component);

        return new_component;
    };

    template <typename T> std::shared_ptr<T> get_component() const
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (int i = 0; i < components.size(); i++)
        {
            std::shared_ptr<Component> component_pointer = components[i];
            std::shared_ptr<T> cast_component = std::dynamic_pointer_cast<T>(component_pointer);
            if (cast_component)
            {
                return cast_component;
            }
        }

        return nullptr;
    };

    template <typename T> bool has_component() const
    {
        return get_component<T>() != nullptr;
    };

    void set_active(bool is_active)
    {
        if (this->is_active == is_active)
        {
            return;
        }

        this->is_active = is_active;
        if (is_active)
        {
            awake();
        }
    }

    inline const std::string& name() const
    {
        return _name;
    }

private:

    std::string _name;
    std::vector<std::shared_ptr<Component>> components;
    bool is_active;

    // Gotta stick this down here so that the components vector gets initted before the transform;
public:
    std::shared_ptr<Transform> transform;
};

#endif // WINTER_ENTITY_H
