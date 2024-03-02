#include "player.hpp"

#include "input.hpp"

float PLAYER_SPEED_WALK = 100.0f;
float PLAYER_SPEED_RUN = 150.0f;
float PLAYER_SPEED_MAX = 1000.0f;
float PLAYER_SPEED_JUMP = 350.0f;
float PLAYER_ACCEL_WALK = 7.0f;
float PLAYER_ACCEL_JUMP_WALK = 3.0f;
float PLAYER_DEACCEL = 2.0f;
float PLAYER_DEACCEL_JUMP = 4.5f;
float PLAYER_DEACCEL_JUMP_SLOW = 2.7f;

void PlayerStateWalkRunJumpUpdate(Player& player)
{
    float& xVel = player.body.vel.x;
    float& yVel = player.body.vel.y;
    int& blocked = player.body.blocked;
    bool left = InputDown(InputButton::Left);
    bool right = InputDown(InputButton::Right);
    bool run = InputDown(InputButton::Run);
    bool jump = InputDown(InputButton::Jump);
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
    if (blocked & Direction::DIR_DOWN)
    {
        if (InputPressed(InputButton::Jump))
        {
            yVel = -PLAYER_SPEED_JUMP;
            blocked &= ~Direction::DIR_DOWN;
        }
        else yVel = 0.0f;
    }

    // Fall.
    else
    {
        if (jump) yVel += PLAYER_DEACCEL_JUMP_SLOW;
        else yVel += PLAYER_DEACCEL_JUMP;
    }

}

enum PlayerState
{
    ST_WALKRUNJUMP
};

Player::Player() : sm({
    StateMachineEntry<Player>(std::nullopt, PlayerStateWalkRunJumpUpdate, std::nullopt),
}, ST_WALKRUNJUMP)
{
    body.termVel = glm::vec2(PLAYER_SPEED_MAX, PLAYER_SPEED_MAX);
}

void Player::Draw()
{
    DrawCircleV(VEC_CAST(body.pos), 50.0f, RED);
}

void Player::Update(float dt)
{
    sm.Execute(*this);
    body.Move(dt);
    if (body.pos.y >= 625.0f) body.blocked |= Direction::DIR_DOWN;
}