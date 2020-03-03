#include "game.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "objects/camera.h"

#include "window.h"
#include "input.h"
#include "world.h"

#include "logger.h"

#include "graphics/spriterenderer.h"

#include "inputcomponenttest.h"

#include "resourceManager.h"

Game::Game()
{

    window = new Window(800, 600, this);
    input = new Input(this);
    world = new World(this);

    // glfwSetInputMode(window->getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    // vsync
    glfwSwapInterval(0);

    loadResources();
    start();

    // render loop
    // -----------
    while (!window->shouldClose())
    {
        float delta = gameTime.beginFrame();

        update(delta);
        render(delta);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window->getGLFWWindow());
        glfwPollEvents();
    }
}

void Game::loadResources()
{
    ResourceManager::instance().loadShader("defaultUnlitShader.vs", "defaultUnlitShader.fs", "defaultShader");
    ResourceManager::instance().loadTexture("container.jpg", "container");
    ResourceManager::instance().loadTexture("awesomeface.png", "awesomeface");
}

void Game::start()
{
    Graphics::Texture2D texture1 = ResourceManager::instance().getTexture("container");

    Entity* sprite = world->instantiate<Entity>("test");
    Graphics::SpriteRenderer* sr = sprite->add<Graphics::SpriteRenderer>("sr");
    sr->setTexture(texture1);

    sprite->add<InputComponentTest>("test");

    Entity* camEntity = world->instantiate<Entity>("mainCam");
    Camera* camera = camEntity->add<OrthoCamera>("orthoCam");

    world->setMainCamera(camera);
}

Game::~Game()
{
    delete world;
}

void Game::update(float deltaTime)
{
    // TODO change to callbacks instead of polling?
    processInput();

    for (auto& entity : world->entities)
    {
        if (entity->isUpdateable())
        {
            entity->update(deltaTime);
        }
    }
}

void Game::render(float)
{
    // TODO aspect ratio

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Camera* cam = world->mainCamera;

    if (cam == nullptr)
    {
        Logger::instance().warn("No main camera setup!");
    }
    else
    {
        int frameBufferWidth;
        int frameBufferHeight;
        window->getSize(frameBufferWidth, frameBufferHeight);

        GraphicContext gContext;
        gContext.view = cam->getView();
        gContext.projection = cam->getProjection(frameBufferWidth, frameBufferHeight);

        for (auto& entity : world->entities)
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
    if (input->isKeyDown(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window->getGLFWWindow(), true);
    }

    if (input->isKeyDown(GLFW_KEY_1))
    {
        // default render mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if (input->isKeyDown(GLFW_KEY_2))
    {
        // wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}
