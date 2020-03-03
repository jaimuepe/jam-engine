#ifndef CONSTRUCTORCONTEXT_H
#define CONSTRUCTORCONTEXT_H

#include <string>
#include <glm/glm.hpp>

class World;
class Input;

struct ConstructorContext
{
    World* world;
    Input* input;
    std::string name;

    glm::vec2 position{0.0f};
    float  rotation{0.0f};
    glm::vec2 scale{1.0f};
};

#endif // CONSTRUCTORCONTEXT_H
