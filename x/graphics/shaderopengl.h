#ifndef SHADEROPENGL_H
#define SHADEROPENGL_H

#include "graphics/shader.h"

#include "glad/glad.h"

namespace graphics

{

class ShaderOpenGL: public Shader
{
public:

    virtual void compile(const char* vCode, const char* fCode) override;

    virtual void use() override;

    virtual void deleteShader() override;

    virtual void setFloat(const char* name, float value) override;

    virtual void setInt(const char* name, int value) override;

    virtual void setVec3(const char* name, const glm::vec3& value) override;

    virtual void setMat4(const char* name, const glm::mat4& value) override;

private:

    GLuint m_ID;
};

} // namespace graphics

#endif // SHADEROPENGL_H
