#include "texture2d.h"

#include <string>

#include <glad/glad.h>

#include "resourcepool.h"

#include "utils/logger.h"

namespace graphics
{

    void Texture2D::generate(unsigned char* data, int width, int height, int nChannels)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &ID);

        GLenum format = nChannels == 3 ? GL_RGB : GL_RGBA;
        GLenum internalFormat = nChannels == 3 ? GL_RGB8 : GL_RGBA8;

        glTextureStorage2D(ID, 1, internalFormat, width, height);

        glTextureSubImage2D(ID, 0, 0, 0, width, height,  format, GL_UNSIGNED_BYTE, data);

        glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateTextureMipmap(ID);

        this->width = width;
        this->height = height;
    }

    void Texture2D::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, this->ID);
    }
}
