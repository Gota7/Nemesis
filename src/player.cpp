#include "player.hpp"

#include "input.hpp"

float PLAYER_SPEED_WALK = 56.0f;
float PLAYER_SPEED_RUN = 80.0f;
float PLAYER_SPEED_MAX = 1000.0f;
float PLAYER_ACCEL_WALK = 15.0f;
float PLAYER_ACCEL_JUMP_WALK = 7.0f;
float PLAYER_DEACCEL = 1.0f;

void PlayerStateWalkRunJumpUpdate(Player& player)
{
    float& xVel = player.body.vel.x;
    // float& yVel = player.body.vel.y;
    int& blocked = player.body.blocked;
    bool left = InputDown(InputButton::Left);
    bool right = InputDown(InputButton::Right);
    bool run = InputDown(InputButton::Run);
    float walkAccel = (blocked & Direction::DIR_DOWN) ? PLAYER_ACCEL_WALK : PLAYER_ACCEL_JUMP_WALK;
    if (left || right)
    {
        float targetSpeed = run ? PLAYER_SPEED_RUN : PLAYER_SPEED_WALK;

        // Handle right.
        if (right)
        {
            if (xVel < targetSpeed)
            {
                xVel += walkAccel;
                if (xVel > targetSpeed) xVel = targetSpeed;
            }
            else if (xVel > targetSpeed)
            {
                xVel -= PLAYER_DEACCEL;
                if (xVel < targetSpeed) xVel = targetSpeed;
            }
        }

        // Handle left.
        if (left)
        {
            if (xVel > -targetSpeed)
            {
                xVel -= walkAccel;
                if (xVel < -targetSpeed) xVel = -targetSpeed;
            }
            else if (xVel < -targetSpeed)
            {
                xVel += PLAYER_DEACCEL;
                if (xVel > -targetSpeed) xVel = -targetSpeed;
            }
        }

    }

    // Deacceleration on ground.
    if ((blocked & Direction::DIR_DOWN) && player.body.vel.y >= 0.0f)
    {

        // Slow right.
        if (xVel > 0.0f)
        {
            if ((blocked & Direction::DIR_RIGHT) && right) xVel = 0.0f;
            else if (xVel > PLAYER_DEACCEL) xVel -= PLAYER_DEACCEL;
            else xVel = 0.0f;
        }

        // Slow left.
        else if (xVel < 0.0f)
        {
            if ((blocked & Direction::DIR_LEFT) && left) xVel = 0.0f;
            else if (xVel < -PLAYER_DEACCEL) xVel += PLAYER_DEACCEL;
            else xVel = 0.0f;
        }

    }

    // Jump logic.

}

enum PlayerState
{
    ST_WALKRUNJUMP
};

Player::Player() : sm({
    StateMachineEntry<Player>(std::nullopt, PlayerStateWalkRunJumpUpdate, std::nullopt),
}, ST_WALKRUNJUMP)
{
    body.blocked |= Direction::DIR_DOWN;
    body.pos.y = 500.0f;
}

void Player::Draw()
{
    DrawCircleV(VEC_CAST(body.pos), 50.0f, RED);
}

void Player::Update(float dt)
{
    sm.Execute(*this);
    body.Move(dt);
    if (body.pos.y >= 500.0f) body.blocked |= Direction::DIR_DOWN;
}