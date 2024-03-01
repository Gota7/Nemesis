#pragma once

#include "body.hpp"
#include "global.hpp"
#include "stateMachine.hpp"

struct Player
{
    Body body;
    StateMachine<Player> sm;

    // Make a new player.
    Player();

    // Draw the player.
    void Draw();

    // Update the player.
    void Update(float dt);

};