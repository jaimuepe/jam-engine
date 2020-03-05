#ifndef MACROS_H
#define MACROS_H

#define STR(s) #s

#define __INTERNAL_COMPONENT_CONSTRUCTOR(TypeName, _renderable, _updateable) \
    TypeName(objects::Entity& owner) \
    : Component(owner) \
    { \
        renderable = _renderable; \
        updateable = _updateable; \
    }

#define COMPONENT_CONSTRUCTOR(TypeName) __INTERNAL_COMPONENT_CONSTRUCTOR(TypeName, false, false)

#define COMPONENT_CONSTRUCTOR_UPDATEABLE(TypeName) __INTERNAL_COMPONENT_CONSTRUCTOR(TypeName, false, true)

#define COMPONENT_CONSTRUCTOR_RENDERABLE(TypeName) __INTERNAL_COMPONENT_CONSTRUCTOR(TypeName, true, false)

#define COMPONENT_CONSTRUCTOR_UPDATEABLE_RENDERABLE(TypeName) __INTERNAL_COMPONENT_CONSTRUCTOR(TypeName, true, true)

#define EMPTY_SETUP_NO_ARGS() void setup() {}

#define CLASS_DESTRUCTOR(TypeName) \
    ~TypeName() \
    { \
        logging::debug(STR(~TypeName)); \
    }

#define CLASS_DESTRUCTOR_BEGIN(TypeName) \
    ~TypeName() \
    { \
        logging::debug(STR(~TypeName));

#define CLASS_DESTRUCTOR_END() \
    }

#define CAMERA_CONSTRUCTOR(TypeName) \
    TypeName(objects::Entity& owner) \
    : Camera(owner) \
    { \
        updateable = false; \
        renderable = false; \
    }

#define CLASS_NON_COPYABLE(TypeName) \
    TypeName(TypeName const&) = delete; \
    void operator=(TypeName const&) = delete;

#endif // MACROS_H
