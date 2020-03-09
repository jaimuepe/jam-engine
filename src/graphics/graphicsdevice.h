#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include <string>

#include "glm/vec4.hpp"

class Game;

namespace graphics
{

class GraphicsDevice
{

public:

    GraphicsDevice(Game* game);

    virtual void init(int width, int height, const std::string& title) = 0;

    virtual void setSize(int width, int height) = 0;

    virtual void getSize(int& width, int& height) const = 0;

    virtual void setFullscreen(bool fullscreen) = 0;

    virtual void clear() = 0;

    virtual void swapBuffers() = 0;
    virtual void pollEvents() = 0;

    glm::vec4 getClearColor() const;

    void setClearColor(glm::vec4 clearColor);

protected:

    Game* m_game;

private:

    glm::vec4 m_clearColor{0.0f, 0.0f, 0.0f, 1.0f};

};

} // namespace graphics

#endif // GRAPHICSDEVICE_H
