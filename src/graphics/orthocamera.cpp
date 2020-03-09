#include "graphics/orthocamera.h"

#include "glm/gtc/matrix_transform.hpp"

#include "objects/entity.h"

#include "utils/constants.h"

namespace graphics
{

OrthoCamera::OrthoCamera(objects::Entity& m_owner): Camera(m_owner), m_size(1.0f)
{
    m_halfWidth = 0.5f * m_size * constants::renderdevices::internalDeviceWidth;
    m_halfHeight = 0.5f * m_size * constants::renderdevices::internalDeviceHeight;
}

void OrthoCamera::setSize(float size)
{
    if (size > 0.0f)
    {
        m_size = size;

        m_halfWidth = 0.5f * size * constants::renderdevices::internalDeviceWidth;
        m_halfHeight = 0.5f * size * constants::renderdevices::internalDeviceHeight;
    }
}

glm::vec2 OrthoCamera::viewportToWorld(float x, float y, float) const
{
    glm::vec2 pos = m_owner.transform.getPosition();
    return glm::vec2
    {
        pos.x + 2.0f * (x - 0.5f) * m_halfWidth, 
        pos.y - 2.0f * (y - 0.5f) * m_halfHeight 
    };
}

glm::mat4 OrthoCamera::getView() const
{
    glm::mat4 view{1.0f};
    view = glm::translate(view, glm::vec3{m_owner.transform.getPosition(), 0.0f});
    return view;
}

glm::mat4 OrthoCamera::getProjection() const
{
    return glm::ortho(-m_halfWidth, m_halfWidth, m_halfHeight, -m_halfHeight, -1.0f, 1.0f);
}

} // namespace objects
