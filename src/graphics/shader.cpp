
#include "shader.h"

#include "glad/glad.h"

#include "resourcepool.h"

#include "utils/logger.h"

#include "glm/gtc/type_ptr.hpp"

namespace graphics
{
    unsigned int Shader::getID() const
    {
        return m_ID;
    }

    void Shader::compile(const char* vCode, const char* fCode)
    {

        // Compiling the shaders

        int success;
        char infoLog[512];

        // Vertex shader

        unsigned int vertexId;
        vertexId = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexId, 1, &vCode, NULL);
        glCompileShader(vertexId);
        glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertexId, 512, NULL, infoLog);
            logging::error("SHADER::VERTEX::COMPILATION_FAILED");
            logging::error(infoLog);
        }

        // fragment shader

        unsigned int fragId;
        fragId = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragId, 1, &fCode, NULL);
        glCompileShader(fragId);
        glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragId, 512, NULL, infoLog);
            logging::error("SHADER::FRAGMENT::COMPILATION_FAILED");
            logging::error(infoLog);
        }

        // program

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexId);
        glAttachShader(m_ID, fragId);
        glLinkProgram(m_ID);

        // print errors if any

        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
            logging::error("SHADER::PROGRAM::LINKING_FAILED");
            logging::error(infoLog);
        }

        // delete the shaders as they're linked into our program now and no longer necessary

        glDeleteShader(vertexId);
        glDeleteShader(fragId);
    }

    void Shader::use() const
    {
        glUseProgram(m_ID);
    }

    void Shader::setFloat(const char* name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_ID, name), value);
    }

     void Shader::setInt(const char* name, int value) const
     {
        glUniform1i(glGetUniformLocation(m_ID, name), value);
     }

     void Shader::setVec3(const char* name, const glm::vec3& value) const
     {
         glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
     }

    void Shader::setMat4(const char* name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(value));
    }
}
