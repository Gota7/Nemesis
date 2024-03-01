#include "game.hpp"

Game::Game() {}

void Game::Draw()
{
    player.Draw();
}

void Game::Update(float dt)
{
    player.Update(dt);
}