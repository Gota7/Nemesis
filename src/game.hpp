#pragma once

#include "player.hpp"

// Main game.
struct Game
{
    Player player;

    // Initialize.
    Game();

    // Draw the game.
    void Draw();

    // Update the game.
    void Update(float dt);

};