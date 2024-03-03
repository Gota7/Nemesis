#pragma once

#include "animator.hpp"

// Forward declare.
struct Scenario;

// Code for a nemesis that reflects and monitors player movements.
struct Nemesis : Actor
{
    Animator animator;
    Body* toFollow;
    Body body;
    PTR<glm::vec2[]> posQueue;
    glm::vec2 axis;
    glm::vec2 prevPos;
    std::size_t queueSize;
    std::size_t posInd = 0;
    Color color;
    bool initRun = true;

    // Make a new nemesis.
    Nemesis(Scenario& scenario, const glm::vec2& pos, const glm::vec2& axis, float delay, Color color);

    // Draw nemesis.
    virtual void Draw() override;

    // Update nemesis.
    virtual void Update(float dt) override;

};