#pragma once

#include "body.hpp"

// Forward declare.
struct Scenario;

// For blocking.
struct Wall : Actor
{
    Scenario& scenario;
    float pos;
    float leftTopLimit;
    float rightBottomLimit;
    int direction;

    // Create a new wall.
    Wall(Scenario& scenario, float pos, float leftTopLimit, float rightBottomLimit, int direction);

    // Draw the wall.
    virtual void Draw() override {}

    // Update the wall.
    virtual void Update(float dt) override;

};