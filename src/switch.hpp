#pragma once

#include "animator.hpp"

// Switch wall.
struct SwitchWall
{
    float pos;
    float leftTopLimit;
    float rightBottomLimit;
    int direction;

    // Make a new switch wall.
    SwitchWall(float pos, float leftTopLimit, float rightBottomLimit, int direction) : pos(pos), leftTopLimit(leftTopLimit), rightBottomLimit(rightBottomLimit), direction(direction) {}

};

// Switch that can create walls.
struct Switch
{

    // Make a switch.
    // Switch(AssetHolder<Tex>& holderTex, const std::string& switchPos, );

};