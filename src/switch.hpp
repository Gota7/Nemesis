#pragma once

#include "animator.hpp"
#include "nemesis.hpp"
#include "numbers.hpp"
#include "wall.hpp"
#include <optional>

// Forward declare.
struct Scenario;

// Switch that can create walls.
struct Switch : Actor
{
    Scenario& scenario;
    Animator animator;
    Numbers numbers;
    PTR<Animator> wallsAnim;
    std::vector<PTR<Wall>> walls;
    std::vector<std::pair<NemesisType, Color>> nemesisTypes;
    std::vector<Body*> playerBodies;
    std::vector<std::size_t> nemesisToKill;
    glm::vec2 pos;
    glm::vec2 hitbox;
    float timer;
    float currTime = 0.0f;
    Color color;
    bool flipWall;
    bool active = false;

    // Make a new switch.
    Switch(Scenario& scenario, std::vector<PTR<Wall>>&& walls, const std::vector<std::pair<NemesisType, Color>>& nemesisTypes, const glm::vec2& pos, const std::optional<std::string>& wallsAnimName, float timer, bool flipWall, Color color);

    // Draw switch.
    virtual void Draw() override;

    // Update switch.
    virtual void Update(float dt) override;

};