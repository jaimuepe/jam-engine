#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;
class Game;

constexpr float internalResolutionX = 1920.0f;
constexpr float internalResolutionY = 1080.0f;

constexpr float internalResolutionAspectRatio = internalResolutionX / internalResolutionY;

class Window
{

public:

    Window(int width, int height);

    void setup(Game* game);

    void getSize(int& width, int& height) const;

    GLFWwindow* getGLFWWindow() const;

    bool shouldClose() const;

private:

    GLFWwindow* m_glfwWindow;
};

#endif // WINDOW_H
