#include "inputopengl.h"

#include "graphics/graphicsdeviceopengl.h"

#include "game.h"

namespace io

{

void InputOpenGL::init()
{
    graphics::GraphicsDeviceOpenGL* gd = static_cast<graphics::GraphicsDeviceOpenGL*>(m_game->getGraphicsDevice());
    GLFWwindow* glfwWindow = gd->getGLFWWindow();

    glfwSetCursorPosCallback(glfwWindow, InputOpenGL::glfwCursorPosCallback);

    glfwSetScrollCallback(glfwWindow, InputOpenGL::glfwScrollCallback);

    glfwSetKeyCallback(glfwWindow, InputOpenGL::glfwKeyCallback);
}

void InputOpenGL::glfwCursorPosCallback(GLFWwindow* window, double posX, double posY)
{
    void* userPointer = glfwGetWindowUserPointer(window);
    if (userPointer)
    {
        Game* game = static_cast<Game*>(userPointer);
        Input* input = static_cast<Input*>(game->getInput());

        float x = (float) posX;
        float y = (float) posY;

        input->notifyCursorCallbacks(x, y);
    }
}

void InputOpenGL::glfwKeyCallback(GLFWwindow* window, int key, int, int action, int)
{
    void* userPointer = glfwGetWindowUserPointer(window);
    if (userPointer)
    {
        Game* game = static_cast<Game*>(userPointer);
        InputOpenGL* input = static_cast<InputOpenGL*>(game->getInput());

        input->m_keyState[key] = action;
    }
}

void InputOpenGL::glfwScrollCallback(GLFWwindow* window, double xOffset, double)
{
    void* userPointer = glfwGetWindowUserPointer(window);
    if (userPointer)
    {
        Game* game = static_cast<Game*>(userPointer);
        InputOpenGL* input = static_cast<InputOpenGL*>(game->getInput());

        float x = (float) xOffset;

        input->notifyScrollCallbacks(x);
    }
}

} // namespace io
