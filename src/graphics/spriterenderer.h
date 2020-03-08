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

class SpriteRenderer : public objects::Component
{

public:

    COMPONENT_CONSTRUCTOR_RENDERABLE(SpriteRenderer)
    CLASS_DESTRUCTOR(SpriteRenderer)

    void setup() override;

    virtual void render(const graphics::RenderContext& context) const override;

    void setShader(const std::string& shader);

    void setShader(const Shader& shader);

    void setTexture(const std::string& texName);

    void setTexture(const Texture2D& texture);

    void setTint(glm::vec3 tint);

    void setRepeat(bool repeat);

private:

    GLuint m_vao;
    GLuint m_vbo;

    Shader m_shader;

    GLfloat m_vertices[16] = {
        // Pos      // Tex
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    bool m_repeat;

    Texture2D m_texture;

    glm::vec3 m_tint{1.0};
};

} // namespace graphics

#endif // SPRITERENDERER_H
