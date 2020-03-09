#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glm/mat4x4.hpp"

namespace graphics
{

class Shader
{

public:

    virtual void compile(const char* vCode, const char* fCode) = 0;

    virtual void use() = 0;

    virtual void deleteShader() = 0;

    virtual void setFloat(const char* name, float value) = 0;

    virtual void setInt(const char* name, int value) = 0;

    virtual void setVec3(const char* name, const glm::vec3& value) = 0;

    virtual void setMat4(const char* name, const glm::mat4& value) = 0;

};

} // namespace graphics

#endif // SHADER_H

