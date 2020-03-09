
#include "io/input.h"

#include "game.h"

#include "utils/logger.h"

namespace io

{

Input::Input(Game* game): m_game(game) {}

bool Input::isKeyDown(int key) const
{
    return m_keyState[key] == GLFW_PRESS;
}

bool Input::isKeyRepeat(int key) const
{
    return m_keyState[key] == GLFW_REPEAT;
}

bool Input::isKeyDownOrRepeat(int key) const
{
    return isKeyDown(key) || isKeyRepeat(key);
}

bool Input::isKeyUp(int key) const
{
    return m_keyState[key] == GLFW_RELEASE;
}

void Input::addCursorPosCallback(const cursorPosCallback &callback)
{
    m_mouseMovedCallbacks.push_back(callback);
}

void Input::notifyCursorCallbacks(float x, float y) const
{
    for (size_t i = 0; i < m_mouseMovedCallbacks.size(); i++)
    {
        m_mouseMovedCallbacks[i](x, y);
    }
}

void Input::addScrollCallback(const scrollCallback &callback)
{
    m_scrollCallbacks.push_back(callback);
}

void Input::notifyScrollCallbacks(float deltaScroll) const
{
    for (size_t i = 0; i < m_scrollCallbacks.size(); i++)
    {
        m_scrollCallbacks[i](deltaScroll);
    }
}

} // namespace io
