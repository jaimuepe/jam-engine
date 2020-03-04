#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "utils/logger.h"

#include "graphics/rendercontext.h"

class GameTime;

namespace objects
{

class Entity;

class Component
{

public:

    Component(objects::Entity& owner);
    virtual ~Component();

    virtual void setup() = 0;

    virtual void update(const GameTime& gameTime);

    virtual void render(const graphics::Context& context);

    bool isRenderable()
    {
        return renderable;
    }

    bool isUpdateable()
    {
        return updateable;
    }

protected:

    objects::Entity& owner;

    bool renderable = false;
    bool updateable = false;
};

} // namespace objects

#endif // ICOMPONENT_H
