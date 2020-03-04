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

        GLuint vbo;

        GLfloat vertices[] = {

            // Pos      // Tex
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f
        };

        // OpenGL 4.5 / ARB_direct_state_access

        // ---- VBO ----

        glCreateBuffers(1, &vbo);
        glNamedBufferStorage(vbo, sizeof(vertices), vertices, 0);

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
        glm::vec2 size = owner.transform.getScale();

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
}
