#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"

#include "logger.h"

Window::Window(int width, int height, Game* game)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    #endif

    // glfw window creation
    // --------------------
    glfwWindow = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (glfwWindow == NULL)
    {
        Logger::instance().fatal("Failed to create GLFW window");
        glfwTerminate();
        state = -1;
        return;
    }

    glfwMakeContextCurrent(glfwWindow);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::instance().fatal("Failed to initialize GLAD");
        state = -1;
        return;
    }

    glfwSetWindowUserPointer(glfwWindow, game);

    state = 0;
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(glfwWindow);
}

void Window::getSize(int& width, int& height) const
{
    glfwGetFramebufferSize(glfwWindow, &width, &height);
}


GLFWwindow* Window::getGLFWWindow() const
{
    return glfwWindow;
}
