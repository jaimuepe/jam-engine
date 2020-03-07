#ifndef WORLD_H
#define WORLD_H

#include <string>

#include <vector>

#include "game.h"

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

    World() = default;

    CLASS_NON_COPYABLE(World)

    ~World();

    void setup(Game* game);

    objects::Entity* create(const std::string& name);

    void setMainCamera(graphics::Camera* mainCamera);
    graphics::Camera* getMainCamera() const;

    std::vector<objects::Entity*> getEntities() const;

private:

    Game* m_game;
    graphics::Camera* m_mainCamera;

    std::vector<objects::Entity*> m_entities;
};

} // namespace objects

#endif // WORLD_H
