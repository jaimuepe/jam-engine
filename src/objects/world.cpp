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
    for (auto entity : m_entities)
    {
        delete entity;
    }
}

void World::setup(Game* game)
{
    m_game = game;
}

Entity* World::create(const std::string &name)
{
    ConstructorContext context;
    context.world = this;
    context.input = m_game->getInput();
    context.resourcePool = m_game->getResourcePool();

    context.name = name;

    Entity* instance = new Entity(context);
    instance->setup();

    m_entities.push_back(instance);

    return instance;
}

graphics::Camera* World::getMainCamera() const
{
    return m_mainCamera;
}

void World::setMainCamera(graphics::Camera *mainCamera)
{
    m_mainCamera = mainCamera;
}

std::vector<objects::Entity*> World::getEntities() const
{
    return this->m_entities;
}

} // namespace objects
