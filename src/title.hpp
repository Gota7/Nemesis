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
    bool darkMode;

    // Make a new title.
    Title(Game& game, AssetHolder<Tex>& holderTex, bool darkMode = false);

    // Draw title.
    virtual void Draw() override;

    // Update title.
    virtual void Update(float dt) override;

};