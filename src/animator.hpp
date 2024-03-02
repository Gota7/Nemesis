#pragma once

#include "body.hpp"
#include "global.hpp"
#include <vector>

// For animating the scene.
struct Animator : Actor
{
    std::vector<Texture2D> textures;
    float frameTime = 0.0f;
    float totalFrameTime;
    std::size_t currFrame = 0;
    std::size_t prevFrame;
    bool lerp;

    // Create a new animator.
    Animator(const std::string& animName, float totalFrameTime, bool lerp = false);

    // Draw animator.
    virtual void Draw() override;

    // Draw in position.
    void DrawPositioned(const glm::vec2& pos = glm::vec2(0.0f), Color tint = WHITE, Rectangle source = { 0.0f, 0.0f, -1.0f, -1.0f });

    // Update animator.
    virtual void Update(float dt) override;

    // DESTROY.
    virtual ~Animator() override;

};