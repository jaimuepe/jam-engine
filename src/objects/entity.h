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

struct ConstructorContext;
class World;

class Entity
{

public:

    Entity(const ConstructorContext& context);
    virtual ~Entity();

    CLASS_NON_COPYABLE(Entity)
    EMPTY_SETUP_NO_ARGS()

    void update(const GameTime& gameTime);
    void render(const graphics::RenderContext& context) const;

    void destroy();

    Transform transform;

    template<class T>
    T* add()
    {
        std::string prettyName = boost::typeindex::type_id<T>().pretty_name();

        auto it = m_components.find(prettyName);
        if (it == m_components.end())
        {
            return this->add<T>(prettyName);
        }

        int index = 0;

        while ((it = m_components.find(prettyName + std::to_string(index))) != m_components.end())
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

        m_components[name] = component;

        logging::debug("Added component " + name + " to entity " + this->m_name);

        if (!m_renderable && component->isRenderable())
        {
            m_renderable = true;
        }

        if (!m_updateable && component->isUpdateable())
        {
            m_updateable = true;
        }

        return component;
    }

    template<class T>
    T& get(const std::string& name)
    {
        // Compile-time sanity check
        static_assert(std::is_base_of<Component, T>::value, "Class is not a Component!");

        return static_cast<T>(*m_components[name]);
    }

    friend class World;

    bool isRenderable()
    {
        return m_renderable;
    }

    bool isUpdateable()
    {
        return m_updateable;
    }

    World* getWorld() const;
    io::Input* getInput() const;
    ResourcePool* getResourcePool() const;

private:

    bool m_renderable = false;
    bool m_updateable = false;

    World* m_world;
    io::Input* m_input;
    ResourcePool* m_resourcePool;

    std::string m_name;

    std::map<std::string, Component*> m_components;
};

} // namespace objects

#endif // ENTITY_H
