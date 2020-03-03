#ifndef CAMERA_H
#define CAMERA_H

#include "objects/entity.h"
#include "objects/component.h"

#include <glm/glm.hpp>

#define CAMERA_CONSTRUCTOR(TypeName) \
    TypeName(Entity& owner) \
    : Camera(owner) \
    { \
        updateable = false; \
        renderable = false; \
    }

class Camera: public Component
{
public:

    COMPONENT_CONSTRUCTOR(Camera, false, false)

    virtual glm::mat4 getView() const = 0;
    virtual glm::mat4 getProjection(int frameBufferWidth, int frameBufferHeight) const = 0;
};

#endif // CAMERA_H
