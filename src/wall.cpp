#include "wall.hpp"

#include "player.hpp"
#include "scenario.hpp"

#define WALL_THICKNESS 1.0f

Wall::Wall(Scenario& scenario, float pos, float leftTopLimit, float rightBottomLimit, int direction) : scenario(scenario), pos(pos), leftTopLimit(leftTopLimit), rightBottomLimit(rightBottomLimit), direction(direction) {}

void WallApply(Wall& wall, Body& body, float rad)
{
    glm::vec2& pos = body.pos;
    glm::vec2& prevPos = body.prevPos;
    glm::vec2 moveAmount = pos - prevPos;
    if (
        (wall.direction & Direction::DIR_UP) &&
        moveAmount.y < 0.0f &&
        pos.y - rad < wall.pos &&
        pos.x + rad > wall.leftTopLimit &&
        pos.x - rad < wall.rightBottomLimit &&
        prevPos.x > wall.pos + rad - WALL_THICKNESS
    )
    {
        pos.y = wall.pos + rad;
        body.vel.y = 0.0f;
        body.blocked |= DIR_UP;
    }
    else if (
        (wall.direction & Direction::DIR_DOWN) &&
        moveAmount.y > 0.0f &&
        pos.y + rad > wall.pos &&
        pos.x + rad > wall.leftTopLimit &&
        pos.x - rad < wall.rightBottomLimit &&
        prevPos.y < wall.pos - rad + WALL_THICKNESS
    )
    {
        pos.y = wall.pos - rad;
        body.vel.y = 0.0f;
        body.blocked |= DIR_DOWN;
    }
    else if (
        (wall.direction & Direction::DIR_LEFT) &&
        moveAmount.x < 0.0f &&
        pos.x - rad < wall.pos &&
        pos.y + rad > wall.leftTopLimit &&
        pos.y - rad < wall.rightBottomLimit && 
        prevPos.x > wall.pos + rad - WALL_THICKNESS
    )
    {
        pos.x = wall.pos + rad;
        body.vel.x = 0.0f;
        body.blocked |= Direction::DIR_LEFT;
    }
    else if (
        (wall.direction & Direction::DIR_RIGHT) &&
        moveAmount.x > 0.0f &&
        pos.x + rad > wall.pos &&
        pos.y + rad > wall.leftTopLimit &&
        pos.y - rad < wall.rightBottomLimit &&
        prevPos.x < wall.pos - rad + WALL_THICKNESS
    )
    {
        pos.x = wall.pos - rad;
        body.vel.x = 0.0f;
        body.blocked |= Direction::DIR_RIGHT;
    }
}

void Wall::Update(float)
{
    for (auto& actor : scenario.actors)
    {
        Player* player = dynamic_cast<Player*>(actor.get());
        if (player) WallApply(*this, player->body, PLAYER_RAD);
    }
}