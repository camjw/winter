#ifndef WINTER_TRANSFORM_SERIALISER_H
#define WINTER_TRANSFORM_SERIALISER_H

#include "component_serialiser.h"
#include <entity/transform.h>
#include <entity/entity.h>
#include <nlohmann/json.hpp>

class TransformSerialiser : public ComponentSerialiser<Transform>
{
    virtual nlohmann::json serialise(Transform* component) override;
    virtual void deserialise(Entity* entity, nlohmann::json data) override;
};

#endif // WINTER_TRANSFORM_SERIALISER_H
