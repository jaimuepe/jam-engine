#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/vec2.hpp"

class Transform
{

public:

    void reset(glm::vec2 position, float rotation, glm::vec2 scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

    glm::vec2 getPosition() const
    {
        return position;
    }

    float getRotation() const
    {
        return rotation;
    }

    glm::vec2 getScale() const
    {
        return scale;
    }

    void translate(glm::vec2 displacement)
    {
        position += displacement;
    }

private:

    glm::vec2 position{0.0f};
    float rotation{0.0f};
    glm::vec2 scale{1.0f};

};

#endif // TRANSFORM_H
