#include "graphicsdeviceopengl.h"

#include "glad/glad.h"

#include "utils/logger.h"

#include "game.h"

#include "utils/constants.h"

namespace graphics

{

void GraphicsDeviceOpenGL::init(int width, int height, const std::string& title)
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
    m_glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
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

    glfwSetWindowUserPointer(m_glfwWindow, m_game);
    glfwSetWindowCloseCallback(m_glfwWindow, glfwWindowCloseCallback);
    glfwSetFramebufferSizeCallback(m_glfwWindow, glfwFramebufferSizeCallback);

    glfwFramebufferSizeCallback(m_glfwWindow, width, height);

    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(0);
}

void GraphicsDeviceOpenGL::setSize(int width, int height)
{
    glfwSetWindowSize(m_glfwWindow, width, height);
}

void GraphicsDeviceOpenGL::getSize(int& width, int& height) const
{
    glfwGetWindowSize(m_glfwWindow, &width, &height);
}


void GraphicsDeviceOpenGL::setFullscreen(bool)
{
    // TODO
}

void GraphicsDeviceOpenGL::clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsDeviceOpenGL::swapBuffers()
{
    glfwSwapBuffers(m_glfwWindow);
}

void GraphicsDeviceOpenGL::pollEvents()
{
    glfwPollEvents();
}

GLFWwindow* GraphicsDeviceOpenGL::getGLFWWindow() const
{
    return m_glfwWindow;
}

void GraphicsDeviceOpenGL::glfwWindowCloseCallback(GLFWwindow* glfwWindow)
{
    void* userPointer = glfwGetWindowUserPointer(glfwWindow);
    if (userPointer)
    {
        static_cast<Game*>(userPointer)->exit();
    }
}

void GraphicsDeviceOpenGL::glfwFramebufferSizeCallback(GLFWwindow *, int width, int height)
{
    float fWidth = static_cast<float>(width);
    float fHeight = static_cast<float>(height);

    float ar = fWidth / fHeight;

    float scaleW = fWidth / constants::renderdevices::internalDeviceWidth;
    float scaleH = fHeight / constants::renderdevices::internalDeviceHeight;

    if (ar > constants::renderdevices::internalAspectRatio) {
       scaleW = scaleH;
    } else {
       scaleH = scaleW;
    }

    float marginX = (fWidth - constants::renderdevices::internalDeviceWidth * scaleW) * 0.5f;
    float marginY = (fHeight - constants::renderdevices::internalDeviceHeight * scaleH) * 0.5f;

    glViewport(
                (int) marginX,
                (int) marginY,
                (int) (constants::renderdevices::internalDeviceWidth * scaleW),
                (int) (constants::renderdevices::internalDeviceHeight * scaleH));
}

} // namespace graphics
