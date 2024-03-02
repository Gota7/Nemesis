#pragma once

#include "player.hpp"
#include "scenario.hpp"

// Main game.
struct Game
{
    Scenario currScenario;

    // Initialize.
    Game();

    // Draw the game.
    void Draw();

    // Update the game.
    void Update(float dt);

};