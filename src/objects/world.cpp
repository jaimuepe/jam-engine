#include "world.h"

#include "objects/constructorContext.h"

#include "objects/entity.h"

#include "gametime.h"

#include "game.h"

#include "io/input.h"

namespace objects
{

World::~World()
{
    for (auto entity : entities)
    {
        delete entity;
    }
}

void World::setup(Game* game)
{
    this->game = game;
}

Entity* World::create(const std::string &name)
{
    ConstructorContext context;
    context.world = this;
    context.input = game->getInput();
    context.resourcePool = game->getResourcePool();

    context.name = name;

    Entity* instance = new Entity(context);
    instance->setup();

    entities.push_back(instance);

    return instance;
}

graphics::Camera* World::getMainCamera() const
{
    return this->mainCamera;
}

void World::setMainCamera(graphics::Camera *mainCamera)
{
    this->mainCamera = mainCamera;
}

std::vector<objects::Entity*> World::getEntities() const
{
    return this->entities;
}

} // namespace objects
