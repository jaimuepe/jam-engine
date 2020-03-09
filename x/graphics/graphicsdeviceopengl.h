#ifndef GRAPHICSDEVICEOPENGL_H
#define GRAPHICSDEVICEOPENGL_H

#include <string>

#include "GLFW/glfw3.h"

#include "graphics/graphicsdevice.h"

class Game;

namespace graphics
{

class GraphicsDeviceOpenGL: public GraphicsDevice
{
public:

    GraphicsDeviceOpenGL(Game* game): GraphicsDevice(game) {};

    virtual void init(int width, int height, const std::string& title) override;

    virtual void setSize(int width, int height) override;

    virtual void getSize(int& width, int& height) const override;

    virtual void setFullscreen(bool fullscreen) override;

    virtual void clear() override;

    virtual void swapBuffers() override;

    virtual void pollEvents() override;

    GLFWwindow* getGLFWWindow() const;

private:

    GLFWwindow* m_glfwWindow;

    static void glfwWindowCloseCallback(GLFWwindow* glfwWindow);
    static void glfwFramebufferSizeCallback(GLFWwindow* glfwWindow, int width, int height);
};

} // namespace graphics

#endif // GRAPHICSDEVICEOPENGL_H
