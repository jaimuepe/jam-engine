#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <functional>

#include "GLFW/glfw3.h"

#include "io/keys.h"
#include "utils/macros.h"

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

    CLASS_NON_COPYABLE(Input)

    void setup(Game* game);

    void addCursorPosCallback(const cursorPosCallback& callback);

    void addScrollCallback(const scrollCallback& callback);

    bool isKeyDown(int key) const;

    bool isKeyRepeat(int key) const;

    bool isKeyDownOrRepeat(int key) const;

    bool isKeyUp(int key) const;

private:

    int m_keyState[KEY_LAST]{};

    std::vector<cursorPosCallback> m_mouseMovedCallbacks;
    std::vector<scrollCallback> m_scrollCallbacks;

    static void glfwScrollCallback(GLFWwindow*, double xOffset, double yOffset);

    static void glfwCursorPosCallback(GLFWwindow*, double xPos, double yPos);
    static void glfwKeyCallback(GLFWwindow*, int key, int scancode, int action, int mods);
};

} // namespace io

#endif // INPUT_H
