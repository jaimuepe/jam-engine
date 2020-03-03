#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "objects/component.h"

#include "graphics/shader.h"
#include "graphics/texture2d.h"

#include "resourceManager.h"

#include "objects/camera.h"

#include "objects/irenderablecomponent.h"

#include "glad/glad.h"

#include <string>

namespace Graphics
{
    class SpriteRenderer : public Component, public IRenderableComponent
    {

    public:

        COMPONENT_CONSTRUCTOR(SpriteRenderer, true, false)

        ~SpriteRenderer();

        void setup() override;

        virtual void render(const GraphicContext& context) override;

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
        Texture2D texture;

        glm::vec3 tint{1.0};
    };
}

#endif // SPRITERENDERER_H
