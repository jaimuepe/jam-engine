
#include "graphics/graphicsdevice.h"

#include "game.h"

namespace graphics

{

GraphicsDevice::GraphicsDevice(Game* game): m_game(game)
{
}

void GraphicsDevice::setClearColor(glm::vec4 clearColor)
{
    m_clearColor = clearColor;
}

glm::vec4 GraphicsDevice::getClearColor() const
{
    return m_clearColor;
}

}
