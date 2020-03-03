#ifndef ORTHOCAMERA_H
#define ORTHOCAMERA_H

#include "objects/component.h"

#include "constructorContext.h"

#include "camera.h"

class OrthoCamera : public Camera
{
public:

    CAMERA_CONSTRUCTOR(OrthoCamera)
    NO_SETUP()

    virtual glm::mat4 getView() const override;
    virtual glm::mat4 getProjection(int frameBufferWidth, int frameBufferHeight) const override;
};

#endif // ORTHOCAMERA_H
