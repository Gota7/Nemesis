#include "title.hpp"

#include "game.hpp"
#include "input.hpp"

#define TITLE_UI_Y 218.0f
#define TITLE_UI_HEIGHT 174.0f
#define TITLE_UI_START_X 634.0f
#define TITLE_UI_PLAY_WIDTH 168.0f
#define TITLE_UI_LEVEL_SELECT_WIDTH 173.0f
#define TITLE_UI_EXIT_WIDTH 211.0f
#define TITLE_UI_ARROW_Y (TITLE_UI_Y + TITLE_UI_HEIGHT + 10.0f)
#define TITLE_UI_PLAY_ARROW_OFF (TITLE_UI_START_X + TITLE_UI_PLAY_WIDTH / 2.0f - 10.0f)
#define TITLE_UI_LEVEL_SELECT_ARROW_OFF (TITLE_UI_START_X + TITLE_UI_PLAY_WIDTH + TITLE_UI_LEVEL_SELECT_WIDTH / 2.0f - 5.0f)
#define TITLE_UI_EXIT_ARROW_OFF (TITLE_UI_START_X + TITLE_UI_PLAY_WIDTH + TITLE_UI_LEVEL_SELECT_WIDTH + TITLE_UI_EXIT_WIDTH / 2.0f - 25.0f)

Title::Title(Game& game, AssetHolder<Tex>& holderTex) : Scene(game), bg(holderTex, "bg_title", FRAME_TIME_DEFAULT), ui(holderTex, "ui_title", FRAME_TIME_DEFAULT), arrow(holderTex, "arrow", FRAME_TIME_DEFAULT) {}

void Title::Draw()
{
    bg.Draw();
    ui.Draw();
    float arrowHalfWidth = arrow.textures[0]->tex.width / 2.0f;
    switch (opt)
    {
        case TitleOption::TITLE_OPT_PLAY:
            arrow.DrawPositioned(glm::vec2(TITLE_UI_PLAY_ARROW_OFF - arrowHalfWidth, TITLE_UI_ARROW_Y));
            break;
        case TitleOption::TITLE_OPT_LEVEL_SELECT:
            arrow.DrawPositioned(glm::vec2(TITLE_UI_LEVEL_SELECT_ARROW_OFF - arrowHalfWidth, TITLE_UI_ARROW_Y));
            break;
        case TitleOption::TITLE_OPT_EXIT:
            arrow.DrawPositioned(glm::vec2(TITLE_UI_EXIT_ARROW_OFF - arrowHalfWidth, TITLE_UI_ARROW_Y));
            break;
        default:
            break;
    }
}

void Title::Update(float dt)
{
    bg.Update(dt);
    ui.Update(dt);
    arrow.Update(dt);

    // Buttons.
    if (InputPressed(InputButton::Left))
    {
        int newOpt = opt - 1;
        if (newOpt <= TitleOption::TITLE_OPT_NONE) newOpt = TitleOption::TITLE_OPT_EXIT;
        opt = (TitleOption)newOpt;
    }
    if (InputPressed(InputButton::Right))
    {
        int newOpt = opt + 1;
        if (newOpt >= TitleOption::TITLE_OPT_COUNT) newOpt = TitleOption::TITLE_OPT_PLAY;
        opt = (TitleOption)newOpt;
    }

    // Mouse.
    static float prevMouseX = 0.0f;
    static float prevMouseY = 0.0f;
    float mouseX = MouseX();
    float mouseY = MouseY();
    if (mouseX != prevMouseX || mouseY != prevMouseY)
    {
        if (mouseY >= TITLE_UI_Y && mouseY < TITLE_UI_Y + TITLE_UI_HEIGHT)
        {
            float levelSelectPos = TITLE_UI_START_X + TITLE_UI_PLAY_WIDTH;
            float exitPos = levelSelectPos + TITLE_UI_LEVEL_SELECT_WIDTH;
            if (mouseX >= TITLE_UI_START_X && mouseX < levelSelectPos)
            {
                opt = TitleOption::TITLE_OPT_PLAY;
            }
            if (mouseX >= levelSelectPos && mouseX < exitPos)
            {
                opt = TitleOption::TITLE_OPT_LEVEL_SELECT;
            }
            if (mouseX >= exitPos && mouseX < exitPos + TITLE_UI_EXIT_WIDTH)
            {
                opt = TitleOption::TITLE_OPT_EXIT;
            }
        } else opt = TitleOption::TITLE_OPT_NONE;
    }
    prevMouseX = mouseX;
    prevMouseY = mouseY;

    // Handle select.
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || InputPressed(InputButton::Jump))
    {
        switch (opt)
        {
            case TitleOption::TITLE_OPT_PLAY:
                Kill();
                break;
            case TitleOption::TITLE_OPT_LEVEL_SELECT:
                game.currScene = nullptr; // TODO!!!
                break;
            case TitleOption::TITLE_OPT_EXIT:
                exit(0);
                break;
            default:
                break;
        }
    }

}