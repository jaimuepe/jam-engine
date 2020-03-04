#ifndef CONSTRUCTORCONTEXT_H
#define CONSTRUCTORCONTEXT_H

#include <string>
#include "glm/glm.hpp"

namespace io
{
class Input;
}

class ResourcePool;

namespace objects
{

class World;

struct ConstructorContext
{
    World* world;
    io::Input* input;
    ResourcePool* resourcePool;

    std::string name;

    glm::vec2 position{0.0f};
    float rotation{0.0f};
    glm::vec2 scale{1.0f};
};

} // namespace objects

#endif // CONSTRUCTORCONTEXT_H
