#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

#include "objects/component.h"

#include "utils/macros.h"

class Window;

namespace graphics
{

class Entity;

class Camera: public objects::Component
{
public:

    COMPONENT_CONSTRUCTOR(Camera)

    virtual glm::mat4 getView() const = 0;
    virtual glm::mat4 getProjection(const Window& window) const = 0;
};

} // namespace graphics

#endif // CAMERA_H
