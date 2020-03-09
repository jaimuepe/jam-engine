#ifndef GAMEINITDATA_H
#define GAMEINITDATA_H

#include <string>

struct GameInitData
{
    struct Window
    {
        std::string title = "default title";
        int screenWidth = 1024;
        int screenHeight = 768;
    };

    Window window;
};

#endif // GAMEINITDATA_H
