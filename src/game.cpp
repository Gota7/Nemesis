#include "game.hpp"

#include <cstdlib>
#include <ctime>

#define START_SCENARIO 0
#define FADE_SEG 1.0f

Game::Game() : holderTex(), logo(holderTex, "7Games", FRAME_TIME_DEFAULT), currScenario(PTR_MAKE(Scenario, *this, START_SCENARIO)), currScenarioNum(START_SCENARIO)
{
    srand(time(NULL));
    origLogoTimer = logoTimer;
}

void Game::Draw()
{
    if (logoTimer > 0.0f)
    {
        logo.Draw();
        float alpha = 0.0f;
        if (logoTimer < FADE_SEG) alpha = 1.0f - logoTimer / FADE_SEG;
        else if (logoTimer > origLogoTimer - FADE_SEG) alpha = (logoTimer - (origLogoTimer - FADE_SEG)) / FADE_SEG;
        if (alpha != 0.0f) DrawRectangle(0, 0, RES_WIDTH, RES_HEIGHT, { 0, 0, 0, (unsigned char)(alpha * 255) });
        return;
    }
    currScenario->Draw();
#ifdef DEBUG
    DrawFPS(10, 10);
#endif
}

void Game::Update(float dt)
{
    if (logoTimer > 0.0f)
    {
        logo.Update(dt);
        logoTimer -= dt;
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