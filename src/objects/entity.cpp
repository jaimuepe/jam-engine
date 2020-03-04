#include "entity.h"

#include "gametime.h"

#include "objects/constructorContext.h"

#include "resourcepool.h"

#include "objects/world.h"
#include "io/input.h"
#include "objects/transform.h"

#include "utils/logger.h"

namespace objects

{

Entity::Entity(const ConstructorContext& context):
    world(context.world), input(context.input), resourcePool(context.resourcePool), name(context.name)
{
    transform.reset(context.position, context.rotation, context.scale);
}

Entity::~Entity()
{
    logging::debug("Destroying entity " + name);
    destroy();
}

void Entity::update(const GameTime& gameTime)
{
    for (auto &comp : components)
    {
        if (comp.second->isUpdateable())
        {
            comp.second->update(gameTime);
        }
    }
}

void Entity::render(const graphics::Context& context)
{
    for (auto &comp : components)
    {
        if (comp.second->isRenderable())
        {
            comp.second->render(context);
        }
    }
}

void Entity::destroy()
{
    for(std::map<std::string, Component*>::iterator itr = components.begin(); itr != components.end(); itr++)
    {
        delete (itr->second);
    }
    components.clear();
}

World* Entity::getWorld() const
{
    return world;
}

io::Input* Entity::getInput() const
{
    return input;
}

ResourcePool* Entity::getResourcePool() const
{
    return resourcePool;
}

} // namespace objects
