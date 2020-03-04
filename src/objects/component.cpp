
#include "component.h"

#include "gametime.h"

namespace objects
{

Component::Component(objects::Entity& owner) : owner(owner) {}

Component::~Component() {}

void Component::render(const graphics::Context&) {}

void Component::update(const GameTime&) {}

} // namespace objects
