#pragma once

#include "animator.hpp"

// Mirror segment.
struct MirrorSegment
{
    glm::vec2 pos;
    std::size_t texInd;

    // Make a new segment.
    MirrorSegment(const glm::vec2& pos, std::size_t texInd) : pos(pos), texInd(texInd) {}

};

// Mirror animation.
struct Mirror : Actor
{
    Animator animator;
    std::vector<MirrorSegment> segments;
    Color color;
    float rot;

    // Create a new mirror.
    Mirror(AssetHolder<Tex>& holderTex, const glm::vec2& startPos, const glm::vec2& dir, Color color);

    // Draw the mirror.
    virtual void Draw() override;

    // Update the mirror.
    virtual void Update(float dt) override;

};