#pragma once

#include "animator.hpp"
#include "global.hpp"
#include "stateMachine.hpp"

#define PLAYER_RAD 50.0f

// Main player you can move.
struct Player : Actor
{
    Animator animator;
    Body body;
    StateMachine<Player> sm;
    Color color;
    float jumpTimer = 0.0f;

    // Make a new player.
    Player(Color color);

    // Draw the player.
    virtual void Draw() override;

    // Update the player.
    virtual void Update(float dt) override;

};