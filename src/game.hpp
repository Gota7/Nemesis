#pragma once

#include "animator.hpp"
#include "assetHolder.hpp"
#include "player.hpp"
#include "scenario.hpp"

// Main game.
struct Game
{
    AssetHolder<Tex> holderTex;
    Animator logo;
    PTR<Scenario> currScenario;
    std::size_t currScenarioNum;
    std::optional<std::size_t> nextScenarioNum;
    float origLogoTimer;
#ifdef DEBUG
    float logoTimer = 0.0f;
#else
    float logoTimer = 3.0f;
#endif

    // Initialize.
    Game();

    // Draw the game.
    void Draw();

    // Update the game.
    void Update(float dt);

    // Reload current scenario.
    void Reload();

    // Advance the scenario.
    void Advance();

};