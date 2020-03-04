#include "gametime.h"

#include <GLFW/glfw3.h>

GameTime::GameTime(): deltaTime(0.0f), lastFrameTime(0.0f) {}

float GameTime::beginFrame()
{
    currentFrameTime = (float) glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    return deltaTime;
}

float GameTime::getCurrentFrameTime() const
{
    return currentFrameTime;
}

float GameTime::getDeltaTime() const
{
    return deltaTime;
}
