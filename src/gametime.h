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

    float deltaTime;
    float currentFrameTime;
    float lastFrameTime;

};

#endif // GAMETIME_H
