#ifndef INPUTCOMPONENTTEST_H
#define INPUTCOMPONENTTEST_H

#include <cmath>

#include "objects/component.h"

#include "io/input.h"

#include "objects/entity.h"

#include "io/keys.h"

#include "utils/macros.h"

#include "gametime.h"

class InputComponentTest: public objects::Component
{
public:

    COMPONENT_CONSTRUCTOR_UPDATEABLE(InputComponentTest)

    CLASS_DESTRUCTOR(InputComponentTest)

    EMPTY_SETUP_NO_ARGS()

    void update(const GameTime& gameTime) override
    {

        float deltaTime = gameTime.getDeltaTime();

        glm::vec2 movement{0.0f};

        if (owner.getInput()->isKeyDownOrRepeat(KEY_W))
        {
            movement.y = -speed;
        }
        else if (owner.getInput()->isKeyDownOrRepeat(KEY_S))
        {
            movement.y = speed;
        }

        if (owner.getInput()->isKeyDownOrRepeat(KEY_A))
        {
            movement.x = -speed;
        }
        else if (owner.getInput()->isKeyDownOrRepeat(KEY_D))
        {
            movement.x = speed;
        }

        owner.transform.setScale(glm::vec2{0.5f + 0.1f * std::cos(3.0f * gameTime.getCurrentFrameTime())});
        owner.transform.rotate(1.5f * deltaTime);
        owner.transform.translate(movement * deltaTime);
    }

    float speed = 160.0f;
};

#endif // INPUTCOMPONENTTEST_H
