#include "gate.hpp"

#include "game.hpp"
#include "scenario.hpp"
#include "wall.hpp"

#define THICKNESS_DEFAULT 25.0f
#define WALL_LEFT_DEFAULT THICKNESS_DEFAULT
#define WALL_RIGHT_DEFAULT (RES_WIDTH - THICKNESS_DEFAULT)
#define CIEL_DEFAULT THICKNESS_DEFAULT
#define FLOOR_DEFAULT (RES_HEIGHT - THICKNESS_DEFAULT)
#define WIDTH_DONT_CARE 100.0f

#define GATE_BR_HEIGHT 525.0f

Gate::Gate(Scenario& scenario, const std::string& type) : animator(scenario.game.holderTex, type, 0.15f)
{
    if (type == "gate_br")
    {
        scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, WALL_LEFT_DEFAULT, 0.0f, RES_HEIGHT, Direction::DIR_LEFT));
        scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, WALL_RIGHT_DEFAULT, 0.0f, GATE_BR_HEIGHT, Direction::DIR_RIGHT));
        scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, GATE_BR_HEIGHT + 1.0f, WALL_RIGHT_DEFAULT, WALL_RIGHT_DEFAULT + WIDTH_DONT_CARE, Direction::DIR_UP));
        scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, CIEL_DEFAULT, 0.0f, RES_WIDTH, Direction::DIR_UP));
        scenario.actors.emplace_back(PTR_MAKE(Wall, scenario, FLOOR_DEFAULT, 0.0f, RES_WIDTH, Direction::DIR_DOWN));
    }
}

void Gate::Draw()
{
    animator.Draw();
}

void Gate::Update(float dt)
{
    animator.Update(dt);
}