#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include <vector>
#include <functional>

class Game;
class Window;

typedef std::function<void(float, float)> cursorPosCallback;
typedef std::function<void(int, int, int, int)> keyCallback;
typedef std::function<void(float, float)> scrollCallback;

class Input
{
public:

    Input(Game* game);

    void addKeyCallback(const keyCallback& callback);

    void addCursorPosCallback(const cursorPosCallback& callback);

    void addScrollCallback(const scrollCallback& callback);

    bool isKeyDown(int key) const;

    bool isKeyRepeat(int key) const;

    bool isKeyDownOrRepeat(int key) const;

    bool isKeyUp(int key) const;

private:

    Game* game;

    int keyState[GLFW_KEY_LAST]{};

    std::vector<keyCallback> keyCallbacks;
    std::vector<cursorPosCallback> mouseMovedCallbacks;
    std::vector<scrollCallback> scrollCallbacks;

    Input(const Input&) = default;
    Input& operator=(const Input&) = default;

    static void glfwScrollCallback(GLFWwindow*, double xOffset, double yOffset);

    static void glfwCursorPosCallback(GLFWwindow*, double xPos, double yPos);
    static void glfwKeyCallback(GLFWwindow*, int key, int scancode, int action, int mods);
};


#endif // INPUT_H
