#include "objects/entity.h"

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
    m_world(context.world), m_input(context.input), m_resourcePool(context.resourcePool), m_name(context.name)
{
    transform.reset(context.position, context.rotation, context.scale);
}

Entity::~Entity()
{
    logging::debug("Destroying entity " + m_name);
    destroy();
}

void Entity::update(const GameTime& gameTime)
{
    for (auto &comp : m_components)
    {
        if (comp.second->isUpdateable())
        {
            comp.second->update(gameTime);
        }
    }
}

void Entity::render(const graphics::RenderContext& context) const
{
    for (auto &comp : m_components)
    {
        if (comp.second->isRenderable())
        {
            comp.second->render(context);
        }
    }
}

void Entity::destroy()
{
    for(std::map<std::string, Component*>::iterator itr = m_components.begin(); itr != m_components.end(); itr++)
    {
        delete (itr->second);
    }
    m_components.clear();
}

World* Entity::getWorld() const
{
    return m_world;
}

io::Input* Entity::getInput() const
{
    return m_input;
}

ResourcePool* Entity::getResourcePool() const
{
    return m_resourcePool;
}

} // namespace objects
