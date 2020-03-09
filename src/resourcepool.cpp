#include "resourcepool.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "stb/stb_image.h"

#include "glad/glad.h"

#include "boost/dll.hpp"
#include "boost/filesystem.hpp"

#include "utils/logger.h"

#include "graphics/texture2d.h"
#include "graphics/shader.h"

static const std::string resourcesPath = boost::dll::program_location().parent_path().string() + "/resources/";

void ResourcePool::init()
{
    loadTexture("fallback/nullTexture.png", "__nullTexture");
}

void ResourcePool::clear()
{
    for(auto itr = m_shaders.begin(); itr != m_shaders.end(); itr++)
    {
        itr->second.deleteShader();
    }
    m_shaders.clear();

    for(std::map<std::string, graphics::Texture2D>::iterator itr = m_textures.begin(); itr != m_textures.end(); itr++)
    {
        unsigned int ID = itr->second.getID();
        glDeleteTextures(1, &ID);
    }
    m_textures.clear();
}

graphics::ShaderImpl ResourcePool::loadShader(const char* vShaderFile, const char* fShaderFile, const std::string& shaderName)
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
    catch (const std::exception&)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    graphics::ShaderImpl shader;
    shader.compile(vertexCode.c_str(), fragmentCode.c_str());

    m_shaders[shaderName] = shader;

    return shader;
}

graphics::ShaderImpl ResourcePool::getShader(const std::string& shaderName)
{
    return m_shaders.at(shaderName);
}

void ResourcePool::loadTexture(const char* textureFile, const std::string& texName)
{
    static const std::string texturesPath = resourcesPath + "textures/";

    const std::string texPath =  texturesPath + textureFile;

    int width;
    int height;
    int nChannels;

    unsigned char* data = stbi_load(texPath.c_str(), &width, &height, &nChannels, 0);

    if (data)
    {
        graphics::Texture2D tex;
        tex.generate(data, width, height, nChannels);

        m_textures[texName] = tex;

        stbi_image_free(data);
    }
    else
    {
        logging::error("Could not load texture " + texName + "!");
    }
}

graphics::Texture2D ResourcePool::getTexture(const std::string& texName)
{
    auto it = m_textures.find(texName);
    if (it == m_textures.end())
    {
        logging::warn("Texture " + texName + " not found!");
        return getTexture("__nullTexture");
    }

    return it->second;
}
