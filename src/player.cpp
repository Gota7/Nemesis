#include "player.hpp"

#include "game.hpp"
#include "input.hpp"
#include "scenario.hpp"

#define PLAYER_SPEED_WALK 225.0f
#define PLAYER_SPEED_RUN 325.0f
#define PLAYER_SPEED_MAX 1000.0f
#define PLAYER_SPEED_JUMP 600.0f
#define PLAYER_ACCEL_WALK 660.0f
#define PLAYER_ACCEL_JUMP_WALK 360.0f
#define PLAYER_DEACCEL 300.0f
#define PLAYER_DEACCEL_JUMP 570.0f
#define PLAYER_DEACCEL_JUMP_SLOW 462.0f
#define PLAYER_COYOTE 0.1f

enum PlayerState
{
    ST_WALKRUNJUMP
};

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
    walkAccel *= player.dt;
    float deaccel = PLAYER_DEACCEL * player.dt;
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
                xVel -= deaccel;
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
                xVel += deaccel;
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
            else if (xVel > deaccel) xVel -= deaccel;
            else xVel = 0.0f;
        }

        // Slow left.
        else if (xVel < 0.0f)
        {
            if ((blocked & Direction::DIR_LEFT) && left) xVel = 0.0f;
            else if (xVel < -deaccel) xVel += deaccel;
            else xVel = 0.0f;
        }

    }

    // Jump logic.
    if (blocked & Direction::DIR_DOWN)
    {
        if (player.jumpTimer > 0.0f)
        {
            yVel = -PLAYER_SPEED_JUMP;
            blocked &= ~Direction::DIR_DOWN;
        }
        else yVel = 0.0f;
    }

    // Fall.
    else
    {
        if (jump) yVel += PLAYER_DEACCEL_JUMP_SLOW * player.dt;
        else yVel += PLAYER_DEACCEL_JUMP * player.dt;
    }

}

Player::Player(Scenario& scenario, const glm::vec2& pos, Color color) : scenario(scenario), animator(scenario.game.holderTex, "blob", FRAME_TIME_DEFAULT), sm({
    StateMachineEntry<Player>(std::nullopt, PlayerStateWalkRunJumpUpdate, std::nullopt),
}, ST_WALKRUNJUMP), color(color)
{
    body.pos = body.prevPos = pos;
    body.termVel = glm::vec2(PLAYER_SPEED_MAX, PLAYER_SPEED_MAX);
}

void Player::Draw()
{
    animator.DrawPositioned(body.pos - glm::vec2(animator.textures[0]->tex.width, animator.textures[0]->tex.height) / 2.0f, color);
}

// void PlayerColCheck(Player& player, const glm::vec2& pos, int)
// {
//     for (auto gate : player.gates)
//     {
//         // if (gate->Intersects(pos, PLAYER_RAD)) return true;
//         gate->
//     }
//     // return false;
// }

void Player::Update(float dt)
{
    this->dt = dt;
    if (InputPressed(InputButton::Jump)) jumpTimer = PLAYER_COYOTE;
    animator.Update(dt);
    sm.Execute(*this);
    body.Move(dt);
    body.blocked = Direction::DIR_NONE;
    jumpTimer = glm::max(0.0f, jumpTimer - dt);
    if (body.pos.x < PLAYER_RAD || body.pos.y < PLAYER_RAD || body.pos.x > RES_WIDTH + PLAYER_RAD || body.pos.y > RES_HEIGHT + PLAYER_RAD) scenario.game.Advance();
    else if (body.flags & Flags::FLAGS_SHALL_DIE) scenario.game.Reload();
}