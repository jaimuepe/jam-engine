
#include "component.h"

#include "gametime.h"

namespace objects
{

Component::Component(objects::Entity& m_owner) : m_owner(m_owner) {}

Component::~Component() {}

void Component::render(const graphics::RenderContext&) const {}

void Component::update(const GameTime&) {}

} // namespace objects
