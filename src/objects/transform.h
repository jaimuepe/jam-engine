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
        m_position = position;
        m_rotation = rotation;
        m_scale = scale;
    }

    void setPosition(const glm::vec2& position)
    {
        m_position = position;
    }

    glm::vec2 getPosition() const
    {
        return m_position;
    }

    void setRotation(float rotation)
    {
        m_rotation = rotation;
    }

    float getRotation() const
    {
        return m_rotation;
    }

    void setScale(const glm::vec2& scale)
    {
        m_scale = scale;
    }

    glm::vec2 getScale() const
    {
        return m_scale;
    }

    void translate(glm::vec2 displacement)
    {
        m_position += displacement;
    }

    void rotate(float increment)
    {
        m_rotation = std::fmod(m_rotation + increment, constants::math::twoPi);
    }

private:

    glm::vec2 m_position{0.0f};
    float m_rotation{0.0f};
    glm::vec2 m_scale{1.0f};

};

#endif // TRANSFORM_H
