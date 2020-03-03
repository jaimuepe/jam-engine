#include "orthocamera.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 OrthoCamera::getView() const
{
    return glm::mat4{1.0f};
}

glm::mat4 OrthoCamera::getProjection(int frameBufferWidth, int frameBufferHeight) const
{
    return glm::ortho(0.0f, static_cast<float>(frameBufferWidth), static_cast<float>(frameBufferHeight), 0.0f, -1.0f, 1.0f);
}
