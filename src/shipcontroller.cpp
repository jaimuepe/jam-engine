
#include "shipcontroller.h"

void ShipController::update(const GameTime& gameTime)
{

    float deltaTime = gameTime.getDeltaTime();


    if (m_owner.getInput()->isKeyDownOrRepeat(KEY_W))
    {
        float rotation = m_owner.transform.getRotation() - constants::math::halfPi;
        float x = cos(rotation);
        float y = sin(rotation);

        m_velocity = m_velocity + m_acceleration * deltaTime * glm::vec2{x, y};

        float currentSpeed = glm::length(m_velocity);
        if (currentSpeed > m_maxSpeed)
        {
            m_velocity = glm::normalize(m_velocity) * m_maxSpeed;
        }
    }

    if (m_owner.getInput()->isKeyDownOrRepeat(KEY_A))
    {
        m_owner.transform.rotate(-m_angularSpeed * deltaTime);
    }
    else if (m_owner.getInput()->isKeyDownOrRepeat(KEY_D))
    {
        m_owner.transform.rotate(m_angularSpeed * deltaTime);
    }

    m_owner.transform.translate(m_velocity * deltaTime);
}
