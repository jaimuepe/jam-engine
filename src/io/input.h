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
typedef std::function<void(float)> scrollCallback;

class Input
{
public:

    Input(Game* game);

    CLASS_NON_COPYABLE(Input)

    virtual void init() = 0;

    void addCursorPosCallback(const cursorPosCallback& callback);

    void notifyCursorCallbacks(float x, float y) const;

    void addScrollCallback(const scrollCallback& callback);

    void notifyScrollCallbacks(float deltaScroll) const;

    bool isKeyDown(int key) const;

    bool isKeyRepeat(int key) const;

    bool isKeyDownOrRepeat(int key) const;

    bool isKeyUp(int key) const;

protected:

    Game* m_game;

    int m_keyState[KEY_LAST]{};

    std::vector<cursorPosCallback> m_mouseMovedCallbacks;
    std::vector<scrollCallback> m_scrollCallbacks;
};

} // namespace io

#endif // INPUT_H
