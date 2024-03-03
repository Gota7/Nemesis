#include "game.hpp"

#define START_SCENARIO 1

Game::Game() : currScenario(PTR_MAKE(Scenario, *this, START_SCENARIO)), currScenarioNum(START_SCENARIO) {}

void Game::Draw()
{
    currScenario->Draw();
#ifdef DEBUG
    DrawFPS(10, 10);
#endif
}

void Game::Update(float dt)
{
    dt = glm::min(dt, 1 / (FPS / 3.0f)); // About the max before problems occur?
    currScenario->Update(dt);
    if (nextScenarioNum)
    {
        currScenario = PTR_MAKE(Scenario, *this, *nextScenarioNum);
        nextScenarioNum = std::nullopt;
    }
}

void Game::Reload()
{
    nextScenarioNum = currScenarioNum;
}

void Game::Advance()
{
    nextScenarioNum = ++currScenarioNum;
}