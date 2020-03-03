#ifndef INPUTCOMPONENTTEST_H
#define INPUTCOMPONENTTEST_H

#include "objects/iupdateablecomponent.h"

#include "objects/component.h"

#include "input.h"

#include "objects/entity.h"

#include <glad/glad.h>

#include <algorithm>

class InputComponentTest: public Component, public IUpdateableComponent
{
public:

    COMPONENT_CONSTRUCTOR(InputComponentTest, false, true)

    void update(float) override
    {

        glm::vec2 movement{0.0f};

        if (owner.getInput()->isKeyDownOrRepeat(GLFW_KEY_W))
        {
            movement.y = -speed;
        }
        else if (owner.getInput()->isKeyDownOrRepeat(GLFW_KEY_S))
        {
            movement.y = speed;
        }

        if (owner.getInput()->isKeyDownOrRepeat(GLFW_KEY_A))
        {
            movement.x = -speed;
        }
        else if (owner.getInput()->isKeyDownOrRepeat(GLFW_KEY_D))
        {
            movement.x = speed;
        }

        owner.transform.translate(movement);
    }

    void setup() override
    {
        updateable = true;
    }

    float speed = 0.01f;
};

#endif // INPUTCOMPONENTTEST_H
