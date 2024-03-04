#pragma once

#include "animator.hpp"
#include "scene.hpp"

// Option.
enum TitleOption
{
    TITLE_OPT_NONE,
    TITLE_OPT_PLAY,
    TITLE_OPT_LEVEL_SELECT,
    TITLE_OPT_EXIT,
    
    TITLE_OPT_COUNT,
};

// Title scene.
struct Title : Scene
{
    Animator bg;
    Animator ui;
    Animator arrow;
    TitleOption opt;

    // Make a new logo.
    Title(Game& game, AssetHolder<Tex>& holderTex);

    // Draw logo.
    virtual void Draw() override;

    // Update logo.
    virtual void Update(float dt) override;

};