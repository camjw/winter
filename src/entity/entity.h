#ifndef WINTER_ENTITY_H
#define WINTER_ENTITY_H

#include <memory>
#include <timer.h>
#include <vector>

class Transform;
class Component;
class Entity
{
public:
    Entity();
    Entity(const std::string& name);

    std::shared_ptr<Transform> transform = nullptr;

    void awake();
    void start();
    void update(const Time& time);
    void late_update(const Time& time);

    template <typename T> std::shared_ptr<T> add_component()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (auto& existing_component : components)
        {
            if (std::dynamic_pointer_cast<T>(existing_component))
            {
                return std::dynamic_pointer_cast<T>(existing_component);
            }
        }

        std::shared_ptr<T> new_component = std::make_shared<T>(this);
        components.push_back(new_component);

        return new_component;
    };

    template <typename T> std::shared_ptr<T> get_component()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        for (auto& existing_component : components)
        {
            if (std::dynamic_pointer_cast<T>(existing_component))
            {
                return std::dynamic_pointer_cast<T>(existing_component);
            }
        }

        return nullptr;
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

    std::string name;

private:
    std::vector<std::shared_ptr<Component>> components;
    bool is_active;
};

#endif // WINTER_ENTITY_H
