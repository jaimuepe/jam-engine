#include "spriterenderer.h"

#include "glm/gtc/matrix_transform.hpp"

#include "utils/logger.h"

#include "objects/entity.h"

#include "resourcepool.h"

namespace graphics
{

void SpriteRenderer::setup()
{
    shader = owner.getResourcePool()->getShader("default");

#ifdef MY_DEBUG
    debugShader = owner.getResourcePool()->getShader("spriteRendererDebug");
#endif

    // OpenGL 4.5 / ARB_direct_state_access

    // ---- VBO ----

    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

    // ---- VAO & linking ---

    glCreateVertexArrays(1, &vao);

    // position + texcoords
    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 4 * sizeof(float));

}

void SpriteRenderer::render(const graphics::Context& context)
{
    glm::vec2 position = owner.transform.getPosition();
    float rotation = owner.transform.getRotation();
    glm::vec2 size = repeat ? glm::vec2{1.0f} : owner.transform.getScale();

    if (texture.ID > 0)
    {
        size.x *= static_cast<float>(texture.getWidth());
        size.y *= static_cast<float>(texture.getHeight());
    }

    float halfWidth = size.x * 0.5f;
    float halfHeight = size.y * 0.5f;

    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3{position, 0.0f});

    model = glm::translate(model, glm::vec3{halfWidth, halfHeight, 0.0f});
    model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3{-halfWidth, -halfHeight, 0.0f});

    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader.use();

    shader.setMat4("model", model);
    shader.setMat4("view", context.view);
    shader.setMat4("projection", context.projection);
    shader.setVec3("tint", tint);

    if (texture.ID > 0)
    {
        texture.bind();
    }

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

#ifdef MY_DEBUG

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
    this->shader = owner.getResourcePool()->getShader(texName);
}

void SpriteRenderer::setShader(const Shader& shader)
{
    this->shader = shader;
}

void SpriteRenderer::setTexture(const std::string& texName)
{
    this->texture = owner.getResourcePool()->getTexture(texName);
}

void SpriteRenderer::setTexture(const Texture2D& texture)
{
    this->texture = texture;
}

void SpriteRenderer::setTint(glm::vec3 tint)
{
    this->tint = tint;
}


void SpriteRenderer::setRepeat(bool repeat)
{
    if (this->repeat != repeat)
    {
        this->repeat = repeat;

        float factorX = repeat ? owner.transform.getScale().x : 1.0f;
        float factorY = repeat ? owner.transform.getScale().y : 1.0f;

        vertices[5] = factorY;
        vertices[7] = factorY;
        vertices[8] = factorX;
        vertices[10] = factorX;
        vertices[12] = factorX;
        vertices[13] = factorY;
        vertices[14] = factorX;
        vertices[15] = factorY;

        glNamedBufferSubData(vbo, 0, sizeof(vertices), vertices);
    }
}

} // namespace graphics
