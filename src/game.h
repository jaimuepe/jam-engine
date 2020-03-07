#ifndef GAME_H
#define GAME_H

#include "gametime.h"

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

    void loadResources();
    void start();

    void update();
    void render();

    Window* getWindow() const
    {
        return m_window;
    }

    io::Input* getInput() const
    {
        return m_input;
    }

    ResourcePool* getResourcePool()
    {
        return m_resourcePool;
    }

private:

    GameTime m_gameTime;

    Window* m_window;
    ResourcePool* m_resourcePool;

    io::Input* m_input;
    objects::World* m_world;

    void processInput();
};

#endif // GAME_H
