#include "graphics/orthocamera.h"

#include "glm/gtc/matrix_transform.hpp"

#include "objects/entity.h"

#include "window.h"

namespace graphics
{

OrthoCamera::OrthoCamera(objects::Entity& owner): Camera(owner), size(1.0f)
{
    halfWidth = 0.5f * size * internalResolutionX;
    halfHeight = 0.5f * size * internalResolutionY;
}

void OrthoCamera::setSize(float size)
{
    if (size > 0.0f)
    {
        this->size = size;

        halfWidth = 0.5f * size * internalResolutionX;
        halfHeight = 0.5f * size * internalResolutionY;
    }
}

glm::mat4 OrthoCamera::getView() const
{
    glm::mat4 view{1.0f};
    view = glm::translate(view, glm::vec3{owner.transform.getPosition(), 0.0f});
    return view;
}

glm::mat4 OrthoCamera::getProjection() const
{
    return glm::ortho(-halfWidth, halfWidth, halfHeight, -halfHeight, -1.0f, 1.0f);
}

} // namespace objects
