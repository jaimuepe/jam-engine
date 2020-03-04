#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <map>

#include "objects/component.h"

#include "objects/transform.h"

#include "io/input.h"

#include "utils/macros.h"

#include "boost/type_index.hpp"

namespace io
{
    class Input;
}

class ResourcePool;
class Transform;

class GameTime;

namespace objects
{

class ConstructorContext;
class World;

class Entity
{

public:

    Entity(const ConstructorContext& context);

    virtual ~Entity();

    EMPTY_SETUP_NO_ARGS()

    void update(const GameTime& gameTime);
    void render(const graphics::Context& context);

    void destroy();

    Transform transform;

    template<class T>
    T* add()
    {
        std::string prettyName = boost::typeindex::type_id<T>().pretty_name();

        auto it = components.find(prettyName);
        if (it == components.end())
        {
            return this->add<T>(prettyName);
        }

        int index = 0;

        while ((it = components.find(prettyName + std::to_string(index))) != components.end())
        {
            index++;
        }

        return this->add<T>(prettyName + std::to_string(index));
    }

    template<class T>
    T* add(const std::string& name)
    {
        // Compile-time sanity check
        static_assert(std::is_base_of<Component, T>::value, "Class is not a Component!");

        T* component = new T(*this);
        component->setup();

        components[name] = component;

        logging::debug("Added component " + name + " to entity " + this->name);

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
    io::Input* getInput() const;
    ResourcePool* getResourcePool() const;

private:

    bool renderable = false;
    bool updateable = false;

    World* world;
    io::Input* input;
    ResourcePool* resourcePool;

    std::string name;

    std::map<std::string, Component*> components;

};

} // namespace objects

#endif // ENTITY_H
