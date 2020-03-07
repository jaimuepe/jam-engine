#ifndef GAMETIME_H
#define GAMETIME_H

class GameTime
{
public:

    GameTime();

    float beginFrame();

    float getDeltaTime() const;

    float getCurrentFrameTime() const;

private:

    float m_deltaTime;
    float m_currentFrameTime;
    float m_lastFrameTime;
};

#endif // GAMETIME_H
