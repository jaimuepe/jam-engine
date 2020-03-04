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

    OrthoCamera(objects::Entity& owner);

    CLASS_DESTRUCTOR(OrthoCamera)

    EMPTY_SETUP_NO_ARGS()

    virtual glm::mat4 getView() const override;
    virtual glm::mat4 getProjection() const override;

    void setSize(float size);

private:

    float size;

    float halfWidth;
    float halfHeight;
};

} // namespace graphics

#endif // ORTHOCAMERA_H
