#include "game.hpp"

#include "logo.hpp"

#define START_SCENARIO 9

Game::Game() : holderTex(), currScenario(PTR_MAKE(Scenario, *this, START_SCENARIO)), currScenarioNum(START_SCENARIO)
{
#ifdef NDEBUG
    currScene = PTR_MAKE(Logo, *this, holderTex);
#endif
}

void Game::Draw()
{
    if (currScene)
    {
        currScene->Draw();
        return;
    }
    currScenario->Draw();
#ifdef DEBUG
    DrawFPS(10, 10);
#endif
}

void Game::Update(float dt)
{
    if (currScene)
    {
        currScene->Update(dt);
        return;
    }
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