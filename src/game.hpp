#pragma once

#include "animator.hpp"
#include "assetHolder.hpp"
#include "player.hpp"
#include "scenario.hpp"

// Main game.
struct Game
{
    AssetHolder<Tex> holderTex;
    PTR<Scenario> currScenario;
    std::size_t currScenarioNum;
    std::optional<std::size_t> nextScenarioNum;

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