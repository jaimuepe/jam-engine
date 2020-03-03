#include "gametime.h"

#include <GLFW/glfw3.h>

GameTime::GameTime(): deltaTime(0.0f), lastFrameTime(0.0f) {}

float GameTime::beginFrame()
{
    float currentTime = (float) glfwGetTime();
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    return deltaTime;
}

float GameTime::getDeltaTime() const
{
    return deltaTime;
}
