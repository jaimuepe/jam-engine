#include "resourceManager.h"

#include "logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <boost/dll.hpp>
#include <boost/filesystem.hpp>

#include "glad/glad.h"

#include <fstream>
#include <iostream>
#include <sstream>

static const std::string resourcesPath = boost::dll::program_location().parent_path().string() + "/resources/";

ResourceManager::ResourceManager()
{
    // stbi_set_flip_vertically_on_load(true);
}

ResourceManager::~ResourceManager()
{
    clear();
}

void ResourceManager::clear()
{
    for(std::map<std::string, Graphics::Shader>::iterator itr = shaders.begin(); itr != shaders.end(); itr++)
    {
         glDeleteProgram(itr->second.ID);
    }
    shaders.clear();

    for(std::map<std::string, Graphics::Texture2D>::iterator itr = textures.begin(); itr != textures.end(); itr++)
    {
        glDeleteTextures(1, &itr->second.ID);
    }
    shaders.clear();
}

Graphics::Shader ResourceManager::loadShader(const char* vShaderFile, const char* fShaderFile, const std::string& shaderName)
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

    Graphics::Shader shader;
    shader.compile(vertexCode.c_str(), fragmentCode.c_str());

    shaders[shaderName] = shader;

    return shader;
}

Graphics::Shader ResourceManager::getShader(const std::string& shaderName)
{
    return shaders[shaderName];
}

Graphics::Texture2D ResourceManager::loadTexture(const char* textureFile, const std::string& texName)
{

    static const std::string texturesPath = resourcesPath + "textures/";

    const std::string texPath =  texturesPath + textureFile;

    int width;
    int height;
    int nChannels;

    unsigned char* data = stbi_load(texPath.c_str(), &width, &height, &nChannels, 0);

    Graphics::Texture2D tex;
    tex.generate(data, width, height, nChannels);

    textures[texName] = tex;

    stbi_image_free(data);

    return tex;
}

Graphics::Texture2D ResourceManager::getTexture(const std::string& texName)
{
    return textures[texName];
}

ResourceManager& ResourceManager::instance()
{
    static ResourceManager instance;
    return instance;
}
