
#include "input.h"

#include "game.h"

#include "window.h"

Input::Input(Game* game)
{
    GLFWwindow* window =  game->getWindow()->getGLFWWindow();

    glfwSetCursorPosCallback(window, Input::glfwCursorPosCallback);

    glfwSetScrollCallback(window, Input::glfwScrollCallback);

    glfwSetKeyCallback(window, Input::glfwKeyCallback);
}

bool Input::isKeyDown(int key) const
{
    return keyState[key] == GLFW_PRESS;
}

bool Input::isKeyRepeat(int key) const
{
    return keyState[key] == GLFW_REPEAT;
}

bool Input::isKeyDownOrRepeat(int key) const
{
    return isKeyDown(key) || isKeyRepeat(key);
}

bool Input::isKeyUp(int key) const
{
    return keyState[key] == GLFW_RELEASE;
}

void Input::addCursorPosCallback(const cursorPosCallback& callback)
{
    mouseMovedCallbacks.push_back(callback);
}

void Input::addScrollCallback(const scrollCallback &callback)
{

    scrollCallbacks.push_back(callback);
}

void Input::addKeyCallback(const keyCallback& callback)
{
    keyCallbacks.push_back(callback);
}

void Input::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    Input* input = game->getInput();

    if (input)
    {
        input->keyState[key] = action;

        std::vector<keyCallback> callbacks = input->keyCallbacks;

        for (size_t i = 0; i < callbacks.size(); i++)
        {
            callbacks[i](key, scancode, action, mods);
        }
    }
}

void Input::glfwCursorPosCallback(GLFWwindow* window, double posX, double posY)
{

    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    Input* input = game->getInput();

    if (input)
    {

        float x = (float) posX;
        float y = (float) posY;

        std::vector<cursorPosCallback> callbacks = input->mouseMovedCallbacks;

        for (size_t i = 0; i < callbacks.size(); i++)
        {
            callbacks[i](x, y);
        }
    }
}

void Input::glfwScrollCallback(GLFWwindow* window, double xOffset, double)
{
    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    Input* input = game->getInput();

    if (input)
    {
        float x = (float) xOffset;
        float y = (float) xOffset;

        std::vector<cursorPosCallback> callbacks = input->scrollCallbacks;

        for (size_t i = 0; i < callbacks.size(); i++)
        {
            callbacks[i](x, y);
        }
    }
}
