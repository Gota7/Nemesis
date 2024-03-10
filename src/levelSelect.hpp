#pragma once

#include "animator.hpp"
#include "numbers.hpp"
#include "scene.hpp"

// Option.
enum LevelSelectOption
{
    LEVEL_SELECT_OPT_NONE,
    LEVEL_SELECT_OPT_TENS_UP,
    LEVEL_SELECT_OPT_TENS_DOWN,
    LEVEL_SELECT_OPT_ONES_UP,
    LEVEL_SELECT_OPT_ONES_DOWN,
    LEVEL_SELECT_OPT_PLAY,
    
    LEVEL_SELECT_OPT_COUNT,
};

// Level select scene.
struct LevelSelect : Scene
{
    Animator bg;
    Animator ui;
    Animator arrow;
    Numbers numbersTens;
    Numbers numbersOnes;
    LevelSelectOption opt;

    // Make a new level select.
    LevelSelect(Game& game, AssetHolder<Tex>& holderTex);

    // Draw level select.
    virtual void Draw() override;

    // Update level select.
    virtual void Update(float dt) override;

};