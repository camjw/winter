#include "transform_serialiser.h"

nlohmann::json TransformSerialiser::serialise(Transform* component)
{
    return nlohmann::json();
}

void TransformSerialiser::deserialise(Entity* entity, nlohmann::json data)
{
    float2 position = float2(data["position"]["x"], data["position"]["y"]);
    entity->transform->position() = position;

    float rotation = data["rotation"];
    entity->transform->rotation() = rotation;

    float2 scale = float2(data["scale"]["x"], data["scale"]["y"]);
    entity->transform->scale() = scale;
}