#include "player.hpp"

#include "input.hpp"

void Player::Draw()
{
    DrawCircleV(VEC_CAST(body.pos), 50.0f, RED);
}

void Player::Update(float dt)
{
    if (InputDown(InputButton::Left)) body.forces.x -= 10.0f;
    if (InputDown(InputButton::Right)) body.forces.x += 10.0f;
    body.Move(dt);
}