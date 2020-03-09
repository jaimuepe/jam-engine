#ifndef INPUTOPENGL_H
#define INPUTOPENGL_H

#include "io/input.h"

class Game;

namespace io

{

class InputOpenGL: public Input
{

public:
    InputOpenGL(Game* game): Input(game) {};

    virtual void init() override;

private:

    static void glfwScrollCallback(GLFWwindow*, double xPos, double yPos);
    static void glfwCursorPosCallback(GLFWwindow*, double xPos, double yPos);
    static void glfwKeyCallback(GLFWwindow*, int key, int scancode, int action, int mods);
};

} // namespace io

#endif // INPUTOPENGL_H
