
#include "component.h"

#include "gametime.h"

namespace objects
{

Component::Component(objects::Entity& m_owner) : m_owner(m_owner) {}

Component::~Component() {}

void Component::render(const graphics::Context&) {}

void Component::update(const GameTime&) {}

} // namespace objects
