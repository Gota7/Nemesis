#include "credits.hpp"

#define FADE_SEG 1.0f

CreditsLauncher::CreditsLauncher(Scenario& scenario) : scenario(scenario)
{
    for (auto& actor : scenario.actors)
    {
        Player* player = dynamic_cast<Player*>(actor.get());
        if (player)
        {
            toFollow = &player->body;
        }
    }
}

void CreditsLauncher::Update(float)
{
    if (toFollow->pos.y >= 500.0f)
    {
        scenario.game.currScene = PTR_MAKE(Credits, scenario.game);
        scenario.game.currScenarioNum = 0;
        scenario.game.nextScenarioNum = 0;
    }
}

Credits::Credits(Game& game) : Scene(game),
title(game.holderTex, "ui_title_logo", FRAME_TIME_DEFAULT),
byGota7(game.holderTex, "by_gota7", FRAME_TIME_DEFAULT),
credits(game.holderTex, "credits", FRAME_TIME_DEFAULT),
thankYou(game.holderTex, "thank_you", FRAME_TIME_DEFAULT)
{}

void Credits::Draw()
{
    DrawRectangle(0, 0, RES_WIDTH, RES_HEIGHT, BLACK);
    title.DrawPositioned(glm::vec2(0.0f), { 255, 255, 255, (unsigned char)(titleA * 255) });
    byGota7.DrawPositioned(glm::vec2(0.0f), { 255, 255, 255, (unsigned char)(byGota7A * 255) });
    credits.DrawPositioned(glm::vec2(0.0f), { 255, 255, 255, (unsigned char)(creditsA * 255) });
    thankYou.DrawPositioned(glm::vec2(0.0f), { 255, 255, 255, (unsigned char)(thankYouA * 255) });
}

void Credits::Update(float dt)
{

    // Anim update.
    title.Update(dt);
    byGota7.Update(dt);
    credits.Update(dt);
    thankYou.Update(dt);

    // Timing. TODO!!!
    game.currScene = PTR_MAKE(Title, game, game.holderTex);

}