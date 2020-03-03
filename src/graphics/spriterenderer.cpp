#include "spriterenderer.h"

#include "logger.h"

#include "objects/entity.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Graphics
{

    SpriteRenderer::~SpriteRenderer()
    {
        Logger::instance().debug("Calling ~SpriteRenderer");
    }

    void SpriteRenderer::setup()
    {
        shader = ResourceManager::instance().getShader("defaultShader");

        GLuint vbo;

        GLfloat vertices[] = {

            // Pos      // Tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
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

    void SpriteRenderer::render(const GraphicContext& context)
    {
        glm::vec2 position = owner.transform.getPosition();
        float rotation = owner.transform.getRotation();
        glm::vec2 scale = owner.transform.getScale();

        if (texture.ID > 0)
        {
            scale.x *= static_cast<float>(texture.getWidth());
            scale.y *= static_cast<float>(texture.getHeight());
        }

        glm::mat4 model{1.0f};
        model = glm::translate(model, glm::vec3(position, 1.0f));
        model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(scale, 1.0f));

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
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}
