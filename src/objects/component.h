#ifndef ICOMPONENT_H
#define ICOMPONENT_H

class Entity;

#define COMPONENT_CONSTRUCTOR(TypeName, _renderable, _updateable) \
    TypeName(Entity& owner) \
    : Component(owner) \
    { \
        renderable = _renderable; \
        updateable = _updateable; \
    }

#define NO_SETUP() \
    void setup() override {}

class Component
{

public:

    Component(Entity& owner);

    virtual void setup() = 0;

    virtual ~Component();

    bool isRenderable()
    {
        return renderable;
    }

    bool isUpdateable()
    {
        return updateable;
    }

protected:

    Entity& owner;

    bool renderable = false;
    bool updateable = false;
};

#endif // ICOMPONENT_H
