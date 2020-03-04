#ifndef WORLD_H
#define WORLD_H

#include "string"

#include "game.h"

#include "objects/entity.h"

#include <vector>

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

    World(World const&) = delete;
    void operator=(World const&) = delete;

    ~World();

    void setup(Game* game);

    objects::Entity* create(const std::string& name);

    void setMainCamera(graphics::Camera* mainCamera);
    graphics::Camera* getMainCamera() const;

    std::vector<objects::Entity*> getEntities() const;

private:

    Game* game;
    graphics::Camera* mainCamera;

    std::vector<objects::Entity*> entities;
};

} // namespace objects

#endif // WORLD_H
