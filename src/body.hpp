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

    // Apply movement.
    void Move(float dt)
    {
        vel.x = glm::min(glm::max(-termVel.x, vel.x), termVel.x);
        vel.y = glm::min(glm::max(-termVel.y, vel.y), termVel.y);
        prevPos = pos;
        pos += vel * dt;
    }

    // Apply movement until collision.
    template <typename T>
    void MovePedantic(float dt, const std::function<bool(T&, const glm::vec2&, int)>& func, T& data)
    {
        vel.x = glm::min(glm::max(-termVel.x, vel.x), termVel.x);
        vel.y = glm::min(glm::max(-termVel.y, vel.y), termVel.y);
        float velX = vel.x * dt;
        if (velX > 0.0f)
        {
            bool hit = false;
            while (velX >= 1.0f)
            {
                if (func(data, pos, Direction::DIR_RIGHT))
                {
                    vel.x = velX = 0.0f;
                    blocked |= Direction::DIR_RIGHT;
                    hit = true;
                    break;
                }
                else pos.x += 1.0f;
                velX -= 1.0f;
            }
            if (!hit)
            {
                if (!func(data, pos + glm::vec2(velX, 0.0f), Direction::DIR_RIGHT))
                {
                    pos.x += velX;
                    blocked &= ~Direction::DIR_RIGHT;
                }
            }
        }
        else if (velX < 0.0f)
        {
            bool hit = false;
            while (velX <= -1.0f)
            {
                if (func(data, pos, Direction::DIR_LEFT))
                {
                    vel.x = velX = 0.0f;
                    blocked |= Direction::DIR_LEFT;
                    hit = true;
                    break;
                }
                else pos.x -= 1.0f;
                velX += 1.0f;
            }
            if (!hit)
            {
                if (!func(data, pos + glm::vec2(velX, 0.0f), Direction::DIR_RIGHT))
                {
                    pos.x += velX;
                    blocked &= ~Direction::DIR_LEFT;
                }
            }
        }
    }

};