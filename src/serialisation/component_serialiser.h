#ifndef WINTER_COMPONENT_SERIALISER_H
#define WINTER_COMPONENT_SERIALISER_H

#include <entity/entity.h>
#include <nlohmann/json.hpp>
#include <entity/component.h>

class JSONComponentSerialiser
{
public:
    virtual void deserialise(Entity* entity, nlohmann::json data) = 0;
};

template <class T>
class ComponentSerialiser : public JSONComponentSerialiser
{
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from component");

public:
    virtual nlohmann::json serialise(T* component) = 0;
    virtual void deserialise(Entity* entity, nlohmann::json data) = 0;
};

#endif // WINTER_COMPONENT_SERIALISER_H
