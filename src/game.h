#ifndef GAME_H
#define GAME_H

#include "gametime.h"

#include "gameinitdata.h"

#include "graphics/graphicsdevice.h"

namespace graphics
{
struct RenderContext;
class Camera;
}

namespace io
{
class Input;
}

namespace objects
{
class World;
}

class Window;
class ResourcePool;

class Game
{
public:

    Game();
    ~Game();

    void init(const GameInitData& data = GameInitData());
    void run();

    virtual void loadResources() = 0;
    virtual void prepareWorld() = 0;

    void update();
    virtual void render(const graphics::RenderContext& renderContext) = 0;

    void exit()
    {
        shouldClose = true;
    }

    void setMainCamera(graphics::Camera* camera)
    {
        m_mainCamera = camera;
    }

    io::Input* getInput() const
    {
        return m_input;
    }

    ResourcePool* getResourcePool()
    {
        return m_resourcePool;
    }

    graphics::GraphicsDevice* getGraphicsDevice()
    {
        return m_graphicsDevice;
    }

protected:

    bool shouldClose = false;

    GameTime m_gameTime;

    graphics::GraphicsDevice* m_graphicsDevice;

    graphics::Camera* m_mainCamera;

    ResourcePool* m_resourcePool;

    io::Input* m_input;
    objects::World* m_world;
};

#endif // GAME_H
