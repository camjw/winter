#ifndef WINTER_CAMERA_SERIALISER_H
#define WINTER_CAMERA_SERIALISER_H

#include "component_serialiser.h"
#include <entity/camera.h>
#include <entity/entity.h>
#include <nlohmann/json.hpp>

class CameraSerialiser : public ComponentSerialiser<Camera>
{
public:
    virtual nlohmann::json serialise(Camera* component) override;
    virtual void deserialise(Entity* entity, nlohmann::json data) override;
};

#endif // WINTER_CAMERA_SERIALISER_H
