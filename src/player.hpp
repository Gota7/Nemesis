#pragma once

#include "body.hpp"
#include "global.hpp"
#include "stateMachine.hpp"

struct Player : Actor
{
    Body body;
    StateMachine<Player> sm;

    // Make a new player.
    Player();

    // Draw the player.
    virtual void Draw() override;

    // Update the player.
    virtual void Update(float dt) override;

};