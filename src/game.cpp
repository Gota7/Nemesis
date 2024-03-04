#include "game.hpp"

#include "logo.hpp"
#include <cstdlib>
#include <ctime>

#define START_SCENARIO 0

Game::Game() : holderTex(), currScenario(PTR_MAKE(Scenario, *this, START_SCENARIO)), currScenarioNum(START_SCENARIO)
{
    srand(time(NULL));
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