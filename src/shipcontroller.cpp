
#include "shipcontroller.h"

void ShipController::update(const GameTime& gameTime)
{

    float deltaTime = gameTime.getDeltaTime();


    if (owner.getInput()->isKeyDownOrRepeat(KEY_W))
    {
        float rotation = owner.transform.getRotation() - constants::math::halfPi;
        float x = cos(rotation);
        float y = sin(rotation);

        glm::vec2 movement{x * speed, y * speed};
        owner.transform.translate(movement * deltaTime);
    }

    if (owner.getInput()->isKeyDownOrRepeat(KEY_A))
    {
        owner.transform.rotate(-angularSpeed * deltaTime);
    }
    else if (owner.getInput()->isKeyDownOrRepeat(KEY_D))
    {
        owner.transform.rotate(angularSpeed * deltaTime);
    }
}
