#pragma once

#include <functional>
#include <glm/glm.hpp>

enum Direction : int
{
    DIR_NONE    = 0 << 0,
    DIR_UP      = 1 << 0,
    DIR_DOWN    = 1 << 1,
    DIR_LEFT    = 1 << 2,
    DIR_RIGHT   = 1 << 3,
};

enum Flags : int
{
    FLAGS_NONE      = 0 << 0,
    FLAGS_SHALL_DIE = 1 << 0,
};

// Actor base.
struct Actor
{
    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual ~Actor() {}
};

// An item that has movement.
struct Body
{
    glm::vec2 pos = glm::vec2(0.0f);
    glm::vec2 prevPos = glm::vec2(0.0f);
    glm::vec2 vel = glm::vec2(0.0f);
    glm::vec2 termVel = glm::vec2(1000.0f, 1000.0f);
    int blocked = DIR_NONE;
    int flags = FLAGS_NONE;

    // Apply movement.
    void Move(float dt)
    {
        vel.x = glm::min(glm::max(-termVel.x, vel.x), termVel.x);
        vel.y = glm::min(glm::max(-termVel.y, vel.y), termVel.y);
        prevPos = pos;
        pos += vel * dt;
    }

};