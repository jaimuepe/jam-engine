#ifndef IRENDERABLECOMPONENT_H
#define IRENDERABLECOMPONENT_H

#include "graphics/graphiccontext.h"

class IRenderableComponent
{

public:
    virtual void render(const GraphicContext& context) = 0;
};

#endif // IRENDERABLECOMPONENT_H
