#ifndef GRAPHICCONTEXT_H
#define GRAPHICCONTEXT_H

#include "glm/mat4x4.hpp"

namespace graphics
{

struct Context
{

public:

    glm::mat4 view;
    glm::mat4 projection;

};

} // namespace graphics

#endif // GRAPHICCONTEXT_H
