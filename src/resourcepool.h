#ifndef RESOURCE_H
#define RESOURCE_H

#include <map>
#include <string>
#include <vector>

#include "utils/logger.h"
#include "utils/macros.h"

#include "graphics/texture2d.h"
#include "graphics/shader.h"

class ResourcePool
{
public:

    CLASS_DESTRUCTOR_BEGIN(ResourcePool)
    clear();
    CLASS_DESTRUCTOR_END()

    graphics::Shader loadShader(const char* vShaderFile, const char* fShaderFile, const std::string& shaderName);
    graphics::Shader getShader(const std::string& shaderName);

    graphics::Texture2D loadTexture(const char* textureFile, const std::string& texName);
    graphics::Texture2D getTexture(const std::string& texName);

    void clear();

private:

    std::map<std::string, graphics::Shader> shaders;
    std::map<std::string, graphics::Texture2D> textures;
};

#endif // RESOURCE_H