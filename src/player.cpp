#include "player.hpp"

#include "gate.hpp"
#include "input.hpp"
#include "scenario.hpp"

#define PLAYER_SPEED_WALK 225.0f
#define PLAYER_SPEED_RUN 275.0f
#define PLAYER_SPEED_MAX 1000.0f
#define PLAYER_SPEED_JUMP 600.0f
#define PLAYER_ACCEL_WALK 11.0f
#define PLAYER_ACCEL_JUMP_WALK 6.0f
#define PLAYER_DEACCEL 5.0f
#define PLAYER_DEACCEL_JUMP 9.5f
#define PLAYER_DEACCEL_JUMP_SLOW 7.7f
#define PLAYER_COYOTE 0.1f

enum PlayerState
{
    ST_INIT,
    ST_WALKRUNJUMP
};

void PlayerStateInit(Player& player)
{
    player.sm.currState = ST_WALKRUNJUMP;
    for (auto& actor : player.scenario.actors)
    {
        Gate* gate = dynamic_cast<Gate*>(actor.get());
        if (gate) player.gates.emplace_back(gate);
    }
}

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
        if (jump) yVel += PLAYER_DEACCEL_JUMP_SLOW;
        else yVel += PLAYER_DEACCEL_JUMP;
    }

}

Player::Player(Scenario& scenario, Color color) : scenario(scenario), animator("blob", 0.15f), sm({
    StateMachineEntry<Player>(std::nullopt, PlayerStateInit, std::nullopt),
    StateMachineEntry<Player>(std::nullopt, PlayerStateWalkRunJumpUpdate, std::nullopt),
}, ST_INIT), color(color)
{
    body.termVel = glm::vec2(PLAYER_SPEED_MAX, PLAYER_SPEED_MAX);
}

void Player::Draw()
{
    animator.DrawPositioned(body.pos - glm::vec2(PLAYER_RAD, PLAYER_RAD), color);
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
    if (InputPressed(InputButton::Jump)) jumpTimer = PLAYER_COYOTE;
    animator.Update(dt);
    sm.Execute(*this);
    // glm::vec2 prevPos = body.pos;
    body.Move(dt);
    body.blocked = Direction::DIR_NONE;
    // for (auto gate : gates) gate->CorrectBody(body, prevPos, PLAYER_RAD);
    // body.MovePedantic<Player>(dt, PlayerColCheck, *this);
    // if (body.pos.y >= 645.0f) body.blocked |= Direction::DIR_DOWN;
    jumpTimer = glm::max(0.0f, jumpTimer - dt);
}