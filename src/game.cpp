#include "game.hpp"

Game::Game() : currScenario(*this, 0) {}

void Game::Draw()
{
    currScenario.Draw();
#ifdef DEBUG
    DrawFPS(10, 10);
#endif
}

void Game::Update(float dt)
{
    currScenario.Update(dt);
}