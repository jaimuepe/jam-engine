#ifndef GRAPHICCONTEXT_H
#define GRAPHICCONTEXT_H

#include <glm/mat4x4.hpp>

struct GraphicContext
{

public:

    glm::mat4 view;
    glm::mat4 projection;

};

#endif // GRAPHICCONTEXT_H
