#include "gate.hpp"

#include "scenario.hpp"
#include "wall.hpp"

#define THICKNESS_DEFAULT 25.0f
#define WALL_LEFT_DEFAULT THICKNESS_DEFAULT
#define WALL_RIGHT_DEFAULT (RES_WIDTH - THICKNESS_DEFAULT)
#define CIEL_DEFAULT THICKNESS_DEFAULT
#define FLOOR_DEFAULT (RES_HEIGHT - THICKNESS_DEFAULT)
#define WIDTH_DONT_CARE 100.0f

#define GATE_BR_HEIGHT 525.0f

Gate::Gate(Scenario& scenario, const std::string& type) : animator(type, 0.15f)
{
    if (type == "gate_br")
    {
        // leftWall = WALL_LEFT_DEFAULT;
        // rightWall = WALL_RIGHT_DEFAULT;
        // ciel = CIEL_DEFAULT;
        // floor = FLOOR_DEFAULT;
        scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, WALL_LEFT_DEFAULT, 0.0f, RES_HEIGHT, Direction::DIR_LEFT));
        scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, WALL_RIGHT_DEFAULT, 0.0f, GATE_BR_HEIGHT, Direction::DIR_RIGHT));
        scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, GATE_BR_HEIGHT + 1.0f, WALL_RIGHT_DEFAULT, WALL_RIGHT_DEFAULT + WIDTH_DONT_CARE, Direction::DIR_UP));
        // scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, CIEL_DEFAULT, 0.0f, RES_WIDTH, Direction::DIR_UP));
        scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, FLOOR_DEFAULT, 0.0f, RES_WIDTH, Direction::DIR_DOWN));
    }
}

// bool Gate::Intersects(const glm::vec2& pos, float rad)
// {
//     if (leftWall >= 0 && pos.x - rad < leftWall) return true;
//     // if (rightWall >= 0 && pos.x + rad > rightWall) return true;
//     // if (ciel >= 0 && pos.y - rad < ciel) return true;
//     // if (floor >= 0 && pos.y + rad > floor) return true;
//     return false;
// }

// void Gate::CorrectBody(Body& body, const glm::vec2& prevPos, float rad)
// {
//     glm::vec2& pos = body.pos;
//     glm::vec2 moveAmount = pos - prevPos;
//     if (ciel >= 0.0f && moveAmount.y < 0.0f && pos.y - rad <= ciel)
//     {
//         pos.y = ciel + rad;
//         body.vel.y = 0.0f;
//         body.blocked |= DIR_UP;
//     }
//     else if (floor >= 0.0f && moveAmount.y > 0.0f && pos.y + rad >= floor)
//     {
//         pos.y = floor - rad;
//         body.vel.y = 0.0f;
//         body.blocked |= DIR_DOWN;
//     }
//     if (leftWall >= 0.0f && moveAmount.x < 0.0f && pos.x - rad <= leftWall)
//     {
//         pos.x = leftWall + rad;
//         body.vel.x = 0.0f;
//         body.blocked |= Direction::DIR_LEFT;
//     }
//     else if (rightWall >= 0.0f && moveAmount.x > 0.0f && pos.x + rad >= rightWall)
//     {
//         pos.x = rightWall - rad;
//         body.vel.x = 0.0f;
//         body.blocked |= Direction::DIR_RIGHT;
//     }
// }

void Gate::Draw()
{
    DrawRectangleV({ WALL_RIGHT_DEFAULT, GATE_BR_HEIGHT }, { WIDTH_DONT_CARE, 5.0f }, GREEN);
    animator.Draw();
}

void Gate::Update(float dt)
{
    animator.Update(dt);
}