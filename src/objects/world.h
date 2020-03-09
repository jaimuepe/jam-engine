#ifndef WORLD_H
#define WORLD_H

#include <string>

#include <vector>

#include "game.h"

#include "gametime.h"

#include "graphics/rendercontext.h"

#include "objects/entity.h"

#include "utils/macros.h"

class Game;
class GameTime;

namespace graphics
{
class Camera;
}

namespace objects
{

class World
{

public:

    World(Game* game);

    CLASS_NON_COPYABLE(World)

    ~World();

    void init();

    objects::Entity* create(const std::string& name);

    void renderEntities(const graphics::RenderContext& context) const;

    void update(const GameTime& gameTime);

private:

    Game* m_game;
    graphics::Camera* m_mainCamera;

    std::vector<objects::Entity*> m_entities;
};

} // namespace objects

#endif // WORLD_H
