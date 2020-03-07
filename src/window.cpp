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
    m_glfwWindow = glfwCreateWindow(width, height, "game", NULL, NULL);
    if (m_glfwWindow == NULL)
    {
        logging::fatal("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_glfwWindow);

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
    glfwSetWindowUserPointer(m_glfwWindow, game);

    glfwSetFramebufferSizeCallback(m_glfwWindow, framebufferSizeCallback);

    int width;
    int height;
    getSize(width, height);

    framebufferSizeCallback(m_glfwWindow, width, height);
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_glfwWindow);
}

void Window::getSize(int& width, int& height) const
{
    glfwGetFramebufferSize(m_glfwWindow, &width, &height);
}

GLFWwindow* Window::getGLFWWindow() const
{
    return m_glfwWindow;
}
