#ifndef INPUTCOMPONENTTEST_H
#define INPUTCOMPONENTTEST_H

#include <cmath>

#include "objects/component.h"

#include "io/input.h"

#include "objects/entity.h"

#include "io/keys.h"

#include "utils/macros.h"

#include "utils/constants.h"

#include "gametime.h"

class ShipController: public objects::Component
{
public:

    COMPONENT_CONSTRUCTOR_UPDATEABLE(ShipController)
    CLASS_DESTRUCTOR(ShipController)

    EMPTY_SETUP_NO_ARGS()

    void update(const GameTime& gameTime);

private:

    float maxSpeed = 200.0f;
    glm::vec2 velocity{0.0f, 0.0f};

    float acceleration = 120.0f;

    float angularSpeed = 3.0f;
};

#endif // INPUTCOMPONENTTEST_H
