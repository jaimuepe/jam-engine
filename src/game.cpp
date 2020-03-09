#include "game.h"

#include "glm/gtc/matrix_transform.hpp"

#include "graphics/camera.h"
#include "graphics/orthocamera.h"

#include "objects/entity.h"

#include "graphics/shader.h"
#include "graphics/spriterenderer.h"
#include "graphics/texture2d.h"

#include "objects/world.h"

#include "io/input.h"
#include "io/keys.h"

#include "utils/logger.h"

#include "utils/xplatformdefinitions.h"

#include "resourcepool.h"

Game::Game()
{
    m_world = new objects::World(this);
    m_resourcePool = new ResourcePool();

    m_input = new io::InputImpl(this);
    m_graphicsDevice = new graphics::GraphicsDeviceImpl(this);
}

void Game::init(const GameInitData& data)
{
    logging::setupLogger();

    // graphics device should be the first to be initialized!
    // i.e. OpenGL - some systems depends on glfw initialized
    m_graphicsDevice->init(data.window.screenWidth, data.window.screenHeight, data.window.title);
    m_resourcePool->init();
    m_input->init();
    m_world->init();

    loadResources();

    prepareWorld();
}

void Game::run()
{
    // render loop
    // -----------
    while (!shouldClose)
    {
        m_gameTime.beginFrame();

        update();

        if (m_mainCamera)
        {
            graphics::RenderContext gContext;
            gContext.view = m_mainCamera->getView();
            gContext.projection = m_mainCamera->getProjection();
            render(gContext);
        }

        m_graphicsDevice->swapBuffers();
        m_graphicsDevice->pollEvents();
    }
}

void Game::update()
{
    m_world->update(m_gameTime);
}

Game::~Game()
{
    delete m_world;
}
