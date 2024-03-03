#pragma once

#include "animator.hpp"

// Forward declare.
struct Scenario;

// Gate.
struct Gate : Actor
{
    Animator animator;
    // float leftWall = -1.0f;
    // float rightWall = -1.0f;
    // float ciel = -1.0f;
    // float floor = -1.0f;

    // Make a new gate.
    Gate(Scenario& scenario, const std::string& type);

    // Correct body.
    // void CorrectBody(Body& body, const glm::vec2& prevPos, float rad);

    // Draw gate.
    virtual void Draw() override;

    // Update gate.
    virtual void Update(float dt) override;

};