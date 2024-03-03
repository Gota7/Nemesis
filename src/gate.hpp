#pragma once

#include "animator.hpp"

// Forward declare.
struct Scenario;

// Gate.
struct Gate : Actor
{
    Animator animator;

    // Make a new gate.
    Gate(Scenario& scenario, const std::string& type);

    // Draw gate.
    virtual void Draw() override;

    // Update gate.
    virtual void Update(float dt) override;

};