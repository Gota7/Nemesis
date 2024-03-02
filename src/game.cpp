#include "game.hpp"

Game::Game() : currScenario(*this, 0) {}

void Game::Draw()
{
    currScenario.Draw();
}

void Game::Update(float dt)
{
    currScenario.Update(dt);
}