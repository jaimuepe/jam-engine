#include "game.h"

#include "glad/glad.h"

#include "glm/gtc/matrix_transform.hpp"

#include "graphics/camera.h"
#include "graphics/orthocamera.h"

#include "objects/entity.h"

#include "graphics/shader.h"
#include "graphics/spriterenderer.h"
#include "graphics/texture2d.h"

#include "window.h"
#include "objects/world.h"

#include "io/input.h"
#include "io/keys.h"

#include "utils/logger.h"

#include "inputcomponenttest.h"

#include "resourcepool.h"

Game::Game()
{
    resourcePool = new ResourcePool();
    input = new io::Input();
    world = new objects::World();
    window = new Window(1024, 768);

    world->setup(this);
    input->setup(this);
    window->setup(this);

    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // vsync
    glfwSwapInterval(0);

    loadResources();
    start();

    // render loop
    // -----------
    while (!window->shouldClose())
    {
        gameTime.beginFrame();

        update();
        render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window->getGLFWWindow());
        glfwPollEvents();
    }
}

void Game::loadResources()
{
    resourcePool->loadShader("defaultUnlitShader.vs", "defaultUnlitShader.fs", "default");
    resourcePool->loadTexture("homer.png", "homer");
    resourcePool->loadTexture("doggo_1080.jpg", "doggo1080");

    /*
    resourcePool->loadTexture("container.jpg", "container");
    resourcePool->loadTexture("awesomeface.png", "awesomeface");
    resourcePool->loadTexture("mr_burns.png", "burns");
    resourcePool->loadTexture("doggo.jpg", "doggo");
    */


#ifdef MY_DEBUG
    resourcePool->loadShader("spriteRendererBoundingBox.vs", "spriteRendererBoundingBox.fs", "spriteRendererDebug");
#endif

}

void Game::start()
{

    graphics::Texture2D bg = resourcePool->getTexture("doggo1080");
    graphics::Texture2D homer = resourcePool->getTexture("homer");

    objects::Entity* bgEntity = world->create("bg");
    bgEntity->transform.setPosition(glm::vec2{-1920.0f * 0.5f, -1080 * 0.5f});

    graphics::SpriteRenderer* sr = bgEntity->add<graphics::SpriteRenderer>();
    sr->setTexture(bg);

    objects::Entity* playerEntity = world->create("player");

    graphics::SpriteRenderer* srPlayer = playerEntity->add<graphics::SpriteRenderer>();
    srPlayer->setTexture(homer);

    playerEntity->add<InputComponentTest>();

    int width;
    int height;
    window->getSize(width, height);

    auto camEntity = world->create("mainCam");

    auto camera = camEntity->add<graphics::OrthoCamera>();

    world->setMainCamera(camera);
}

Game::~Game()
{
    delete world;
}

void Game::update()
{
    // TODO change to callbacks instead of polling?
    processInput();

    for (auto& entity : world->getEntities())
    {
        if (entity->isUpdateable())
        {
            entity->update(gameTime);
        }
    }
}

void Game::render()
{
    graphics::Camera* cam = world->getMainCamera();

    if (cam == nullptr)
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        logging::warn("No main camera setup!");
    }
    else
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        GLint m_viewport[4];
        glGetIntegerv(GL_VIEWPORT, m_viewport);

        glEnable(GL_SCISSOR_TEST);
        glScissor(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDisable(GL_SCISSOR_TEST);

        graphics::Context gContext;
        gContext.view = cam->getView();
        gContext.projection = cam->getProjection();

        for (auto& entity : world->getEntities())
        {
            if (entity->isRenderable())
            {
                entity->render(gContext);
            }
        }
    }
}

void Game::processInput()
{
    if (input->isKeyDown(KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window->getGLFWWindow(), true);
    }

#ifdef MY_DEBUG

    if (input->isKeyDown(KEY_1))
    {
        // default render mode
        glEnable(GL_BLEND);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if (input->isKeyDown(KEY_2))
    {
        // wireframe mode
        glDisable(GL_BLEND);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (input->isKeyDown(KEY_KP_1))
    {
        if (world->getMainCamera())
        {
            static_cast<graphics::OrthoCamera*>(world->getMainCamera())->setSize(1.0f);
        }
    }
    else if (input->isKeyDown(KEY_KP_2))
    {
        if (world->getMainCamera())
        {
            static_cast<graphics::OrthoCamera*>(world->getMainCamera())->setSize(2.0f);
        }
    }

#endif

}
