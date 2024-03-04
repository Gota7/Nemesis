#include "logo.hpp"

#define FADE_SEG 1.0f

Logo::Logo(Game& game, AssetHolder<Tex>& holderTex) : Scene(game), holderTex(holderTex), logo(holderTex, "7Games", FRAME_TIME_DEFAULT)
{
    origLogoTimer = logoTimer;
}

void Logo::Draw()
{
    logo.Draw();
    float alpha = 0.0f;
    if (logoTimer < FADE_SEG) alpha = 1.0f - logoTimer / FADE_SEG;
    else if (logoTimer > origLogoTimer - FADE_SEG) alpha = (logoTimer - (origLogoTimer - FADE_SEG)) / FADE_SEG;
    if (alpha != 0.0f) DrawRectangle(0, 0, RES_WIDTH, RES_HEIGHT, { 0, 0, 0, (unsigned char)(alpha * 255) });
}

void Logo::Update(float dt)
{
    logo.Update(dt);
    logoTimer -= dt;
    if (logoTimer <= 0.0f) game.currScene = PTR_MAKE(Title, game, holderTex);
}