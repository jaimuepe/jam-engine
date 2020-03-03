#ifndef WINDOW_H
#define WINDOW_H

class GLFWwindow;
class Game;

class Window
{

public:

    Window(int width, int height, Game* game);

    void getSize(int& width, int& height) const;

    GLFWwindow* getGLFWWindow() const;

    bool shouldClose() const;

private:

    int state;
    GLFWwindow* glfwWindow;
};

#endif // WINDOW_H
