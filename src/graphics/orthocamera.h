#ifndef ORTHOCAMERA_H
#define ORTHOCAMERA_H

#include "objects/component.h"

#include "graphics/camera.h"

#include "utils/macros.h"

class Window;

namespace graphics
{

class OrthoCamera : public Camera
{
public:

    CAMERA_CONSTRUCTOR(OrthoCamera)
    CLASS_DESTRUCTOR(OrthoCamera)

    EMPTY_SETUP_NO_ARGS()

    virtual glm::mat4 getView() const override;
    virtual glm::mat4 getProjection(const Window& window) const override;
};

} // namespace graphics

#endif // ORTHOCAMERA_H
