#include "window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "objects/world.h"

#include "utils/logger.h"

void framebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height)
{
    void* userPointer = glfwGetWindowUserPointer(glfwWindow);

    if (userPointer)
    {
        Game* game = static_cast<Game*>(userPointer);
        Window* window = game->getWindow();

        float fWidth = static_cast<float>(width);
        float fHeight = static_cast<float>(height);

        float fBaseWidth = static_cast<float>(window->baseWidth);
        float fBaseHeight = static_cast<float>(window->baseHeight);

        float ar = fWidth / fHeight;

        float scaleW = fWidth / fBaseWidth;
        float scaleH = fHeight / fBaseHeight;

        if (ar > window->baseAspectRatio) {
            scaleW = scaleH;
        } else {
            scaleH = scaleW;
        }

        float marginX = (fWidth - fBaseWidth * scaleW) * 0.5f;
        float marginY = (fHeight - fBaseHeight * scaleH) * 0.5f;

        glViewport((int) marginX, (int) marginY, (int) (fBaseWidth * scaleW), (int) (fBaseHeight * scaleH));
    }
}

Window::Window(int width, int height)
    : baseWidth(width), baseHeight(height), baseAspectRatio(static_cast<float>(width) / static_cast<float>(height))
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    #endif

    // glfw window creation
    // --------------------
    glfwWindow = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (glfwWindow == NULL)
    {
        logging::fatal("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(glfwWindow);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        logging::fatal("Failed to initialize GLAD");
        return;
    }
}

void Window::setup(Game* game)
{
    glfwSetWindowUserPointer(glfwWindow, game);

    glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);

    framebufferSizeCallback(glfwWindow, baseWidth, baseHeight);
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
