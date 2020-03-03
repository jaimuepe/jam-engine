#ifndef GAMETIME_H
#define GAMETIME_H

class GameTime
{
public:

    GameTime();

    float beginFrame();

    float getDeltaTime() const;

private:

    float deltaTime;
    float lastFrameTime;

};

#endif // GAMETIME_H
