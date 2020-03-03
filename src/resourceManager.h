#ifndef RESOURCE_H
#define RESOURCE_H

#include <map>
#include <string>
#include <vector>

#include "graphics/texture2d.h"
#include "graphics/shader.h"

class ResourceManager
{
public:

    Graphics::Shader loadShader(const char* vShaderFile, const char* fShaderFile, const std::string& shaderName);
    Graphics::Shader getShader(const std::string& shaderName);

    Graphics::Texture2D loadTexture(const char* textureFile, const std::string& texName);
    Graphics::Texture2D getTexture(const std::string& texName);

    void clear();

    static ResourceManager& instance();

private:

    ResourceManager();
    ~ResourceManager();
    ResourceManager(const ResourceManager&) = default;
    ResourceManager& operator=(const ResourceManager&) = default;

    std::map<std::string, Graphics::Shader> shaders;
    std::map<std::string, Graphics::Texture2D> textures;

};

#endif // RESOURCE_H
