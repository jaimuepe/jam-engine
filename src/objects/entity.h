#ifndef ENTITY_H
#define ENTITY_H

#include "objects/component.h"
#include "transform.h"

#include "objects/irenderablecomponent.h"
#include "objects/iupdateablecomponent.h"

#include <string>
#include <map>

class ConstructorContext;

class Input;
class Transform;
class World;

class Entity
{

public:

    Entity(const ConstructorContext& context);

    virtual ~Entity();

    virtual void setup();

    void update(float deltaTime);
    void render(const GraphicContext& context);

    void destroy();

    Transform transform;

    template<class T>
    T* add(const std::string& name)
    {
        // Compile-time sanity check
        static_assert(std::is_base_of<Component, T>::value, "Class is not a Component!");

        T* component = new T(*this);
        component->setup();

        components[name] = component;

        if (!renderable && component->isRenderable())
        {
            renderable = true;
        }

        if (!updateable && component->isUpdateable())
        {
            updateable = true;
        }

        return component;
    }

    template<class T>
    T& get(const std::string& name)
    {
        // Compile-time sanity check
        static_assert(std::is_base_of<Component, T>::value, "Class is not a Component!");

        return static_cast<T>(*components[name]);
    }

    friend class World;

    bool isRenderable()
    {
        return renderable;
    }

    bool isUpdateable()
    {
        return updateable;
    }

    World* getWorld() const;
    Input* getInput() const;

private:

    bool renderable = false;
    bool updateable = false;

    World* world;
    Input* input;

    std::string name;

    std::map<std::string, Component*> components;

};

#endif // ENTITY_H
