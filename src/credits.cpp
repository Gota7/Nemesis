#include "credits.hpp"

#include "logo.hpp"

#define FADE_SEG 1.0f

#define TITLE_BEG 0.0f
#define TITLE_END (TITLE_BEG + 5.0f)
#define BY_7GAMES_BEG 1.5f
#define BY_7GAMES_END TITLE_END
#define CREDITS_BEG (BY_7GAMES_END + 0.1f)
#define CREDITS_END (CREDITS_BEG + 5.0f)
#define THANK_YOU_BEG (CREDITS_END + 0.1f)
#define THANK_YOU_END (THANK_YOU_BEG + 5.0f)
#define SCENE_END (THANK_YOU_END + 0.25f)

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
by7Games(game.holderTex, "by_7Games", FRAME_TIME_DEFAULT),
credits(game.holderTex, "credits", FRAME_TIME_DEFAULT),
thankYou(game.holderTex, "thank_you", FRAME_TIME_DEFAULT)
{}

void Credits::Draw()
{
    DrawRectangle(0, 0, RES_WIDTH, RES_HEIGHT, BLACK);
    title.DrawPositioned(glm::vec2(0.0f), { 255, 255, 255, (unsigned char)(titleA * 255) });
    by7Games.DrawPositioned(glm::vec2(0.0f), { 255, 255, 255, (unsigned char)(by7GamesA * 255) });
    credits.DrawPositioned(glm::vec2(0.0f), { 255, 255, 255, (unsigned char)(creditsA * 255) });
    thankYou.DrawPositioned(glm::vec2(0.0f), { 255, 255, 255, (unsigned char)(thankYouA * 255) });
}

float CreditsGetAlpha(float currTime, float startTime, float endTime)
{
    if (currTime < startTime || currTime >= endTime) return 0.0f;
    float nearDiff = currTime - startTime;
    if (nearDiff < FADE_SEG) return nearDiff / FADE_SEG;
    float farDiff = endTime - currTime;
    if (farDiff < FADE_SEG) return farDiff / FADE_SEG;
    return 1.0f;
}

void Credits::Update(float dt)
{

    // Anim update.
    title.Update(dt);
    by7Games.Update(dt);
    credits.Update(dt);
    thankYou.Update(dt);

    // Timing.
    currTime += dt;
    titleA = CreditsGetAlpha(currTime, TITLE_BEG, TITLE_END);
    by7GamesA = CreditsGetAlpha(currTime, BY_7GAMES_BEG, BY_7GAMES_END);
    creditsA = CreditsGetAlpha(currTime, CREDITS_BEG, CREDITS_END);
    thankYouA = CreditsGetAlpha(currTime, THANK_YOU_BEG, THANK_YOU_END);
    if (currTime >= SCENE_END) game.currScene = PTR_MAKE(Logo, game, game.holderTex);

}