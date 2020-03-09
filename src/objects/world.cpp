#include "objects/world.h"

#include "objects/constructorContext.h"

#include "objects/entity.h"

#include "gametime.h"

#include "graphics/camera.h"

#include "game.h"

#include "io/input.h"

namespace objects
{

World::World(Game* game): m_game(game) {}

World::~World()
{
    for (auto entity : m_entities)
    {
        delete entity;
    }
}

void World::init()
{

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

void World::update(const GameTime& gameTime)
{
    for (auto& entity : m_entities)
    {
        if (entity->isUpdateable())
        {
            entity->update(gameTime);
        }
    }
}

void World::renderEntities(const graphics::RenderContext& context) const
{
    for (auto entity : m_entities)
    {
        if (entity->isRenderable())
        {
            entity->render(context);
        }
    }
}

} // namespace objects
