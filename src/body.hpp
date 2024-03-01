#pragma once

#include <glm/glm.hpp>

enum Direction : int
{
    DIR_NONE    = 0 << 0,
    DIR_UP      = 1 << 0,
    DIR_DOWN    = 1 << 1,
    DIR_LEFT    = 1 << 2,
    DIR_RIGHT   = 1 << 3,
};

// An item that has movement.
struct Body
{
    glm::vec2 pos = glm::vec2(0.0f);
    glm::vec2 vel = glm::vec2(0.0f);
    int blocked = DIR_NONE;

    // Apply movement.
    void Move(float dt)
    {
        pos += vel * dt;
    }

};