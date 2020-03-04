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
        return window;
    }

    io::Input* getInput() const
    {
        return input;
    }

    ResourcePool* getResourcePool()
    {
        return resourcePool;
    }

private:

    GameTime gameTime;

    Window* window;
    ResourcePool* resourcePool;

    io::Input* input;
    objects::World* world;

    void processInput();
};

#endif // GAME_H
