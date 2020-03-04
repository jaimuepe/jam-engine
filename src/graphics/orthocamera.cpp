#include "graphics/orthocamera.h"

#include "glm/gtc/matrix_transform.hpp"

#include "objects/entity.h"

#include "window.h"

namespace graphics
{

glm::mat4 OrthoCamera::getView() const
{
    glm::mat4 view{1.0f};
    // view = glm::translate(view, glm::vec3{0.5f * owner.transform.getPosition(), 0.0f});
    return view;
}

glm::mat4 OrthoCamera::getProjection(const Window& window) const
{

    float baseWidth = static_cast<float>(window.baseWidth);
    float baseHeight = static_cast<float>(window.baseHeight);
    // float baseAspectRatio = static_cast<float>(window.baseAspectRatio);

    return glm::ortho(-baseWidth * 0.5f, baseWidth * 0.5f, baseHeight * 0.5f, -baseHeight * 0.5f, -1.0f, 1.0f);
}

} // namespace objects
