#include "resourcepool.h"

#include <fstream>
#include <iostream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "glad/glad.h"

#include "boost/dll.hpp"
#include "boost/filesystem.hpp"

#include "utils/logger.h"

#include "graphics/texture2d.h"
#include "graphics/shader.h"

static const std::string resourcesPath = boost::dll::program_location().parent_path().string() + "/resources/";

void ResourcePool::clear()
{
    for(std::map<std::string, graphics::Shader>::iterator itr = shaders.begin(); itr != shaders.end(); itr++)
    {
         glDeleteProgram(itr->second.ID);
    }
    shaders.clear();

    for(std::map<std::string, graphics::Texture2D>::iterator itr = textures.begin(); itr != textures.end(); itr++)
    {
        glDeleteTextures(1, &itr->second.ID);
    }
    textures.clear();
}

graphics::Shader ResourcePool::loadShader(const char* vShaderFile, const char* fShaderFile, const std::string& shaderName)
{

    static const std::string shadersPath = resourcesPath + "shaders/";

    const std::string vPath = shadersPath + vShaderFile;
    const std::string fPath = shadersPath + fShaderFile;

    std::string vertexCode;
    std::string fragmentCode;

    try
    {
        // Open files
        std::ifstream vertexShaderFile(vPath);
        std::ifstream fragmentShaderFile(fPath);
        std::stringstream vShaderStream, fShaderStream;

        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    graphics::Shader shader;
    shader.compile(vertexCode.c_str(), fragmentCode.c_str());

    shaders[shaderName] = shader;

    return shader;
}

graphics::Shader ResourcePool::getShader(const std::string& shaderName)
{
    return shaders[shaderName];
}

graphics::Texture2D ResourcePool::loadTexture(const char* textureFile, const std::string& texName)
{

    static const std::string texturesPath = resourcesPath + "textures/";

    const std::string texPath =  texturesPath + textureFile;

    int width;
    int height;
    int nChannels;

    unsigned char* data = stbi_load(texPath.c_str(), &width, &height, &nChannels, 0);

    graphics::Texture2D tex;
    tex.generate(data, width, height, nChannels);

    textures[texName] = tex;

    stbi_image_free(data);

    return tex;
}

graphics::Texture2D ResourcePool::getTexture(const std::string& texName)
{
    auto it = textures.find(texName);
    if (it == textures.end())
    {
        logging::warn("Texture " + texName + " not found!");
    }

    return it->second;
}
