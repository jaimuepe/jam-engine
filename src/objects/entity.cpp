#include "entity.h"

#include "constructorContext.h"

#include "world.h"
#include "input.h"
#include "transform.h"

#include "logger.h"

#define _ENTITY_CONSTRUCTOR_

Entity::Entity(const ConstructorContext& context):
    world(context.world), input(context.input), name(context.name)
{
    transform.reset(context.position, context.rotation, context.scale);
}

Entity::~Entity()
{
    Logger::instance().debug("Destroying entity " + name);
    destroy();
}

void Entity::setup()
{
}

void Entity::update(float deltaTime)
{
    for (auto &comp : components)
    {
        if (comp.second->isUpdateable())
        {
            dynamic_cast<IUpdateableComponent*>(comp.second)->update(deltaTime);
        }
    }
}

void Entity::render(const GraphicContext& context)
{
    for (auto &comp : components)
    {
        if (comp.second->isRenderable())
        {
            dynamic_cast<IRenderableComponent*>(comp.second)->render(context);
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

Input* Entity::getInput() const
{
    return input;
}
