#include "camera_serialiser.h"
#include <maths/colour.h>

nlohmann::json CameraSerialiser::serialise(Camera* component)
{}

void CameraSerialiser::deserialise(Entity* entity, nlohmann::json data)
{
    std::shared_ptr<Camera> camera = entity->add_component<Camera>();

    colour clear_colour = colour(data["clear_colour"]["r"], data["clear_colour"]["g"], data["clear_colour"]["b"]);
    camera->set_clear_colour(clear_colour);
}