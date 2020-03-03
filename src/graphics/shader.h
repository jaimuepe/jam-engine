#ifndef SHADER_H
#define SHADER_H

#include <glm/mat4x4.hpp>

#include <string>

namespace Graphics
{

    class Shader
    {

    public:

        // program ID)
        unsigned int ID;

        void compile(const char* vCode, const char* fCode);

        // Activates the shader
        void use() const;

        // uniform functions
        void setFloat(const char* name, float value) const;

        void setInt(const char* name, int value) const;

        void setVec3(const char* name, const glm::vec3& value) const;

        void setMat4(const char* name, const glm::mat4& value) const;
    };
}

#endif // SHADER_H
