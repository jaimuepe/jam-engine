#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include "utils/logger.h"

#include "graphics/rendercontext.h"

#include "utils/macros.h"

class GameTime;

namespace objects
{

class Entity;

class Component
{

public:

    Component(Entity& m_owner);
    virtual ~Component();

    CLASS_NON_COPYABLE(Component)

    virtual void setup() = 0;

    virtual void update(const GameTime& gameTime);

    virtual void render(const graphics::RenderContext& context);

    bool isRenderable()
    {
        return m_renderable;
    }

    bool isUpdateable()
    {
        return m_updateable;
    }

protected:

    Entity& m_owner;

    bool m_renderable = false;
    bool m_updateable = false;
};

} // namespace objects

#endif // ICOMPONENT_H
