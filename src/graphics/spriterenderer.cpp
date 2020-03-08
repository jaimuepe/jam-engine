#include "spriterenderer.h"

#include "glm/gtc/matrix_transform.hpp"

#include "utils/logger.h"

#include "objects/entity.h"

#include "resourcepool.h"

namespace graphics
{

void SpriteRenderer::setup()
{
    m_shader = m_owner.getResourcePool()->getShader("default");

    // OpenGL 4.5 / ARB_direct_state_access

    // ---- VBO ----

    glCreateBuffers(1, &m_vbo);
    glNamedBufferStorage(m_vbo, sizeof(m_vertices), m_vertices, GL_DYNAMIC_STORAGE_BIT);

    // ---- VAO & linking ---

    glCreateVertexArrays(1, &m_vao);

    // position + texcoords
    glEnableVertexArrayAttrib(m_vao, 0);
    glVertexArrayAttribFormat(m_vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, 4 * sizeof(float));

}

void SpriteRenderer::render(const graphics::RenderContext& context) const
{
    glm::vec2 position = m_owner.transform.getPosition();
    float rotation = m_owner.transform.getRotation();
    glm::vec2 size = m_repeat ? glm::vec2{1.0f} : m_owner.transform.getScale();

    if (m_texture.isValid())
    {
        size.x *= static_cast<float>(m_texture.getWidth());
        size.y *= static_cast<float>(m_texture.getHeight());
    }

    float halfWidth = size.x * 0.5f;
    float halfHeight = size.y * 0.5f;

    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3{position, 0.0f});

    model = glm::translate(model, glm::vec3{halfWidth, halfHeight, 0.0f});
    model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3{-halfWidth, -halfHeight, 0.0f});

    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_shader.use();

    m_shader.setMat4("model", model);
    m_shader.setMat4("view", context.view);
    m_shader.setMat4("projection", context.projection);
    m_shader.setVec3("tint", m_tint);

    if (m_texture.isValid())
    {
        m_texture.bind();
    }

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

#ifdef MY_DEBUG

    static graphics::Shader debugShader = owner.getResourcePool()->getShader("spriteRendererDebug");

    debugShader.use();
    debugShader.setMat4("model", model);
    debugShader.setMat4("view", context.view);
    debugShader.setMat4("projection", context.projection);

    GLint polygonMode;
    glGetIntegerv(GL_POLYGON_MODE, &polygonMode);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(polygonMode));

#endif

    glBindVertexArray(0);
}

void SpriteRenderer::setShader(const std::string& texName)
{
    m_shader = m_owner.getResourcePool()->getShader(texName);
}

void SpriteRenderer::setShader(const Shader& shader)
{
    m_shader = shader;
}

void SpriteRenderer::setTexture(const std::string& texName)
{
    m_texture = m_owner.getResourcePool()->getTexture(texName);
}

void SpriteRenderer::setTexture(const Texture2D& texture)
{
    m_texture = texture;
}

void SpriteRenderer::setTint(glm::vec3 tint)
{
    m_tint = tint;
}


void SpriteRenderer::setRepeat(bool repeat)
{
    if (m_repeat != repeat)
    {
        m_repeat = repeat;

        float factorX = repeat ? m_owner.transform.getScale().x : 1.0f;
        float factorY = repeat ? m_owner.transform.getScale().y : 1.0f;

        m_vertices[5] = factorY;
        m_vertices[7] = factorY;
        m_vertices[8] = factorX;
        m_vertices[10] = factorX;
        m_vertices[12] = factorX;
        m_vertices[13] = factorY;
        m_vertices[14] = factorX;
        m_vertices[15] = factorY;

        glNamedBufferSubData(m_vbo, 0, sizeof(m_vertices), m_vertices);
    }
}

} // namespace graphics
