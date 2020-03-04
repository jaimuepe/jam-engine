#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <string>

#include "glad/glad.h"

#include "objects/component.h"

#include "graphics/shader.h"
#include "graphics/texture2d.h"

#include "utils/macros.h"

namespace graphics
{

namespace
{
    constexpr GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
}

class SpriteRenderer : public objects::Component
{

public:

    COMPONENT_CONSTRUCTOR_RENDERABLE(SpriteRenderer)
    CLASS_DESTRUCTOR(SpriteRenderer)

    void setup() override;

    virtual void render(const graphics::Context& context) override;

    void setShader(const Shader& shader)
    {
        this->shader = shader;
    }

    void setTexture(const Texture2D& texture)
    {
        this->texture = texture;
    }

    void setTint(glm::vec3 tint)
    {
        this->tint = tint;
    }

private:

    // TODO default shader?

    GLuint vao;

    Shader shader;

#ifdef MY_DEBUG
    Shader debugShader;
#endif

    Texture2D texture;

    glm::vec3 tint{1.0};
};

} // namespace graphics

#endif // SPRITERENDERER_H
