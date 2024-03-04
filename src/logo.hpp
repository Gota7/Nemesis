#pragma once

#include "animator.hpp"
#include "game.hpp"
#include "scene.hpp"
#include "title.hpp"

// Logo scene.
struct Logo : Scene
{
    AssetHolder<Tex>& holderTex;
    Animator logo;
    float logoTimer = 3.0f;
    float origLogoTimer;

    // Make a new logo.
    Logo(Game& game, AssetHolder<Tex>& holderTex);

    // Draw logo.
    virtual void Draw() override;

    // Update logo.
    virtual void Update(float dt) override;

};