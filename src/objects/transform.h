#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>

#include "glm/vec2.hpp"

#include "utils/constants.h"

class Transform
{

public:

    void reset(const glm::vec2& position, float rotation, const glm::vec2& scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

    void setPosition(const glm::vec2& position)
    {
        this->position = position;
    }

    glm::vec2 getPosition() const
    {
        return position;
    }

    void setRotation(float rotation)
    {
        this->rotation = rotation;
    }

    float getRotation() const
    {
        return rotation;
    }

    void setScale(const glm::vec2& scale)
    {
        this->scale = scale;
    }

    glm::vec2 getScale() const
    {
        return scale;
    }

    void translate(glm::vec2 displacement)
    {
        position += displacement;
    }

    void rotate(float increment)
    {
        rotation = std::fmod(rotation + increment, constants::math::twoPi);
    }

private:

    glm::vec2 position{0.0f};
    float rotation{0.0f};
    glm::vec2 scale{1.0f};

};

#endif // TRANSFORM_H
