#pragma once

#include "animator.hpp"
#include "global.hpp"
#include "stateMachine.hpp"

#define PLAYER_RAD 50.0f

// Forward declare.
struct Scenario;

// Main player you can move.
struct Player : Actor
{
    Scenario& scenario;
    Animator animator;
    Body body;
    StateMachine<Player> sm;
    Color color;
    float jumpTimer = 0.0f;
    float dt;

    // Make a new player.
    Player(Scenario& scenario, const glm::vec2& pos, Color color);

    // Draw the player.
    virtual void Draw() override;

    // Update the player.
    virtual void Update(float dt) override;

};