#ifndef XPLATFORMDEFINITIONS_H
#define XPLATFORMDEFINITIONS_H

#ifdef OPENGL

#include "graphics/graphicsdeviceopengl.h"
#include "graphics/shaderopengl.h"
#include "io/inputopengl.h"

namespace graphics
{
typedef GraphicsDeviceOpenGL GraphicsDeviceImpl;
typedef ShaderOpenGL ShaderImpl;
} // namespace graphics

namespace io
{
typedef InputOpenGL InputImpl;
} // namespace io

#endif

#endif // XPLATFORMDEFINITIONS_H
