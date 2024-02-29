#pragma once

#include <glm/glm.hpp>

// An item that has acceleration.
struct Accelerator
{
    glm::vec2 pos = glm::vec2(0.0f);
    glm::vec2 vel = glm::vec2(0.0f);
    glm::vec2 termVel = glm::vec2(100.0f, 100.0f);
    glm::vec2 forces = glm::vec2(0.0f);
    float mass = 1.0f;

    // Apply movement and reset foreces.
    void Move(float dt)
    {
        glm::vec2 accel = mass * forces;
        vel += accel * dt;
        vel.x = glm::min(glm::max(-termVel.x, vel.x), termVel.x);
        vel.y = glm::min(glm::max(-termVel.y, vel.y), termVel.y);
        pos += vel * dt;
        forces = glm::vec2(0.0f);
    }

};