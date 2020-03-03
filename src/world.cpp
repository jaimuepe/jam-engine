#include "world.h"

#include "objects/entity.h"

#include "gametime.h"

#include "input.h"

World::World(Game* game)
{
    this->game = game;
}

World::~World()
{
    for (auto entity : entities)
    {
        delete entity;
    }
}
