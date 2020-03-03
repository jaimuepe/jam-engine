#ifndef GAME_H
#define GAME_H

#include "gametime.h"

#include "graphics/texture2d.h"
#include "graphics/shader.h"

#include "objects/orthocamera.h"

#include "objects/entity.h"

#include <glm/glm.hpp>

class Input;
class World;
class Window;

class Shader;
class FlyCamera;
class Texture;

class Game
{
public:

    Game();
    ~Game();

    void loadResources();
    void start();

    void update(float deltaTime);
    void render(float deltaTime);

    Window* getWindow()
    {
        return window;
    }

    Input* getInput()
    {
        return input;
    }

private:

    GameTime gameTime;

    Input* input;
    World* world;
    Window* window;

    void processInput();
};

#endif // GAME_H
