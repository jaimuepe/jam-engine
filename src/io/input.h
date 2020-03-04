#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <functional>

#include "io/keys.h"

#include "GLFW/glfw3.h"

class Game;
class Window;

namespace io

{

typedef std::function<void(float, float)> cursorPosCallback;
typedef std::function<void(float, float)> scrollCallback;

class Input
{
public:

    Input() = default;

    void setup(Game* game);

    void addCursorPosCallback(const cursorPosCallback& callback);

    void addScrollCallback(const scrollCallback& callback);

    bool isKeyDown(int key) const;

    bool isKeyRepeat(int key) const;

    bool isKeyDownOrRepeat(int key) const;

    bool isKeyUp(int key) const;

private:

    int keyState[KEY_LAST]{};

    std::vector<cursorPosCallback> mouseMovedCallbacks;
    std::vector<scrollCallback> scrollCallbacks;

    Input(const Input&) = default;
    Input& operator=(const Input&) = default;

    static void glfwScrollCallback(GLFWwindow*, double xOffset, double yOffset);

    static void glfwCursorPosCallback(GLFWwindow*, double xPos, double yPos);
    static void glfwKeyCallback(GLFWwindow*, int key, int scancode, int action, int mods);
};

} // namespace io

#endif // INPUT_H
