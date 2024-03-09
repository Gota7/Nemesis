#pragma once

#include "body.hpp"
#include "global.hpp"
#include <functional>
#include <memory>
#include <vector>

// Forward declare.
struct Game;

// Scenario loading.
struct Scenario
{
    Game& game;
    std::vector<PTR<Actor>> actors;
    bool haltUpdate = false;

    // Load a scenario.
    Scenario(Game& game, std::size_t num);

    // Draw the scenario.
    void Draw();

    // Update the scenario,
    void Update(float dt);

};