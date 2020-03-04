#include "window.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "objects/world.h"

#include "utils/logger.h"

void framebufferSizeCallback(GLFWwindow*, int width, int height)
{

    float fWidth = static_cast<float>(width);
    float fHeight = static_cast<float>(height);

    float ar = fWidth / fHeight;

    float scaleW = fWidth / internalResolutionX;
    float scaleH = fHeight / internalResolutionY;

    if (ar > internalResolutionAspectRatio) {
        scaleW = scaleH;
    } else {
        scaleH = scaleW;
    }

    float marginX = (fWidth - internalResolutionX * scaleW) * 0.5f;
    float marginY = (fHeight - internalResolutionY * scaleH) * 0.5f;

    glViewport((int) marginX, (int) marginY, (int) (internalResolutionX * scaleW), (int) (internalResolutionY * scaleH));
}

Window::Window(int width, int height)
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

    int width;
    int height;
    getSize(width, height);

    framebufferSizeCallback(glfwWindow, width, height);
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
