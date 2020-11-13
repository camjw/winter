#ifndef WINTER_ENTITY_H
#define WINTER_ENTITY_H

#include "component.h"
#include <memory>
#include <vector>

class Entity
{
private:
    std::vector<std::unique_ptr<Component>> components;
};

#endif // WINTER_ENTITY_H
