#include "scene.hpp"

#include "game.hpp"

void Scene::Kill()
{
    game.currScene = nullptr;
}