#pragma once

#include "accelerator.hpp"
#include "global.hpp"

struct Player
{
    Accelerator body;

    // Draw the player.
    void Draw();

    // Update the player.
    void Update(float dt);

};