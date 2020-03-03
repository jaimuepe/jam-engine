#ifndef WORLD_H
#define WORLD_H

#include "string"

#include "game.h"

#include "objects/entity.h"

#include "objects/camera.h"

#include "constructorContext.h"

#include <vector>

class Game;
class GameTime;

class World
{

public:

    World(Game* game);

    World(World const&) = delete;
    void operator=(World const&) = delete;

    template<class T>
    T* instantiate(const std::string& name)
    {
        // Compile-time sanity check
        static_assert(std::is_base_of<Entity, T>::value, "Class is not an Entity!");

        ConstructorContext context;
        context.world = this;
        context.input = game->getInput();
        context.name = name;

        T* instance = new T(context);
        instance->setup();

        entities.push_back(instance);

        return instance;
    }

    void setMainCamera(Camera* mainCamera)
    {
        this->mainCamera = mainCamera;
    }

    friend class Game;

private:

    Game* game;
    Camera* mainCamera;

    std::vector<Entity*> entities;

    ~World();
};


#endif // WORLD_H
