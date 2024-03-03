#pragma once

#include "animator.hpp"

// For drawing numbers.
struct Numbers : Actor
{
    Animator animator;
    glm::vec2 pos;
    unsigned int num;
    Color color;

    // Make a new number. Position is the top right corner.
    Numbers(AssetHolder<Tex>& holderTex, const glm::vec2& pos, unsigned int num, Color color);

    // Draw the number.
    virtual void Draw() override;

    // Update the number.
    virtual void Update(float dt) override;

};