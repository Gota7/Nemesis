#pragma once

#include "animator.hpp"
#include "pathFollower.hpp"

// Forward declare.
struct Scenario;

// Nemesis type.
enum class NemesisType
{
    Mirror,
    Chase,
    Path,
    Frozen,
    Tank,
    Racer,
};

// Code for a nemesis that reflects and monitors player movements.
struct Nemesis : Actor
{
    Scenario& scenario;
    Animator animator;
    Body* toFollow;
    Body body;
    PTR<glm::vec2[]> posQueue;
    PTR<PathFollower> path;
    PTR<PathFollower> racerPath;
    glm::vec2 axis;
    glm::vec2 shootDir;
    glm::vec2 prevPos;
    float speed;
    std::size_t queueSize;
    std::size_t posInd = 0;
    Color color;
    NemesisType type;
    bool initRun = true;

    // Make a new nemesis.
    Nemesis(Scenario& scenario, PTR<PathFollower> path, PTR<PathFollower> racerPath, const glm::vec2& pos, const glm::vec2& axis, const glm::vec2& shootDir, float delay, float speed, NemesisType type, Color color);

    // Draw nemesis.
    virtual void Draw() override;

    // Update nemesis.
    virtual void Update(float dt) override;

};