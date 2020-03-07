#include "gametime.h"

#include "GLFW/glfw3.h"

GameTime::GameTime(): m_deltaTime(0.0f), m_lastFrameTime(0.0f) {}

float GameTime::beginFrame()
{
    m_currentFrameTime = (float) glfwGetTime();
    m_deltaTime = m_currentFrameTime - m_lastFrameTime;
    m_lastFrameTime = m_currentFrameTime;

    return m_deltaTime;
}

float GameTime::getCurrentFrameTime() const
{
    return m_currentFrameTime;
}

float GameTime::getDeltaTime() const
{
    return m_deltaTime;
}
