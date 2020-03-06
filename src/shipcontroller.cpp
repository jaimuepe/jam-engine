
#include "shipcontroller.h"

void ShipController::update(const GameTime& gameTime)
{

    float deltaTime = gameTime.getDeltaTime();


    if (owner.getInput()->isKeyDownOrRepeat(KEY_W))
    {
        float rotation = owner.transform.getRotation() - constants::math::halfPi;
        float x = cos(rotation);
        float y = sin(rotation);

        velocity = velocity + acceleration * deltaTime * glm::vec2{x, y};

        float currentSpeed = glm::length(velocity);
        if (currentSpeed > maxSpeed)
        {
            velocity = glm::normalize(velocity) * maxSpeed;
        }
    }

    if (owner.getInput()->isKeyDownOrRepeat(KEY_A))
    {
        owner.transform.rotate(-angularSpeed * deltaTime);
    }
    else if (owner.getInput()->isKeyDownOrRepeat(KEY_D))
    {
        owner.transform.rotate(angularSpeed * deltaTime);
    }

    owner.transform.translate(velocity * deltaTime);
}
