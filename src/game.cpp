#include "game.hpp"

Game::Game()
{
    player.body.pos = glm::vec2(50.0f, 50.0f);
}

void Game::Draw()
{
    player.Draw();
}

void Game::Update(float dt)
{
    player.Update(dt);
}