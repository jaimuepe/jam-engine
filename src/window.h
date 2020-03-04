#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;
class Game;

class Window
{

public:

    const int baseWidth;
    const int baseHeight;

    const float baseAspectRatio;

    Window(int width, int height);

    void setup(Game* game);

    void getSize(int& width, int& height) const;

    GLFWwindow* getGLFWWindow() const;

    bool shouldClose() const;

private:

    GLFWwindow* glfwWindow;
};

#endif // WINDOW_H
