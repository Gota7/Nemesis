#include "levelSelect.hpp"

#include "game.hpp"
#include "input.hpp"

#define LEVEL_SELECT_UI_BLOCK_WIDTH 175.0f
#define LEVEL_SELECT_UI_BLOCK_HEIGHT 175.0f
#define LEVEL_SELECT_UI_UP_Y 20.0f
#define LEVEL_SELECT_UI_DOWN_Y 350.0f
#define LEVEL_SELECT_UI_TENS_X 350.0f
#define LEVEL_SELECT_UI_ONES_X 680.0f

#define LEVEL_SELECT_UI_PLAY_X 910.0f
#define LEVEL_SELECT_UI_PLAY_Y 190.0f

#define LEVEL_SELECT_UI_ARROW_Y 520.0f
#define LEVEL_SELECT_UI_TENS_ARROW_OFF 415.0f
#define LEVEL_SELECT_UI_ONES_ARROW_OFF 740.0f
#define LEVEL_SELECT_UI_PLAY_ARROW_OFF 990.0f

LevelSelect::LevelSelect(Game& game, AssetHolder<Tex>& holderTex) :
    Scene(game),
    bg(holderTex, "bg_level_select", FRAME_TIME_DEFAULT),
    ui(holderTex, "ui_level_select", FRAME_TIME_DEFAULT),
    arrow(holderTex, "arrow", FRAME_TIME_DEFAULT),
    numbersTens(holderTex, glm::vec2(400.0f, 210.0f), 0, WHITE),
    numbersOnes(holderTex, glm::vec2(730.0f, 210.0f), 0, WHITE)
{}

void LevelSelect::Draw()
{
    bg.Draw();
    ui.Draw();
    numbersTens.Draw();
    numbersOnes.Draw();
    float arrowHalfWidth = arrow.textures[0]->tex.width / 2.0f;
    switch (opt)
    {
        case LevelSelectOption::LEVEL_SELECT_OPT_TENS_UP:
        case LevelSelectOption::LEVEL_SELECT_OPT_TENS_DOWN:
            arrow.DrawPositioned(glm::vec2(LEVEL_SELECT_UI_TENS_ARROW_OFF - arrowHalfWidth, LEVEL_SELECT_UI_ARROW_Y));
            break;
        case LevelSelectOption::LEVEL_SELECT_OPT_ONES_UP:
        case LevelSelectOption::LEVEL_SELECT_OPT_ONES_DOWN:
            arrow.DrawPositioned(glm::vec2(LEVEL_SELECT_UI_ONES_ARROW_OFF - arrowHalfWidth, LEVEL_SELECT_UI_ARROW_Y));
            break;
        case LevelSelectOption::LEVEL_SELECT_OPT_PLAY:
            arrow.DrawPositioned(glm::vec2(LEVEL_SELECT_UI_PLAY_ARROW_OFF - arrowHalfWidth, LEVEL_SELECT_UI_ARROW_Y));
            break;
        default:
            break;
    }
}

void LevelSelect::Update(float dt)
{
    bg.Update(dt);
    ui.Update(dt);
    arrow.Update(dt);
    numbersTens.Update(dt);
    numbersOnes.Update(dt);

    // Buttons.
    if (InputPressed(InputButton::Left))
    {
        int newOpt = opt - 1;
        if (newOpt == LevelSelectOption::LEVEL_SELECT_OPT_TENS_DOWN) newOpt = LevelSelectOption::LEVEL_SELECT_OPT_TENS_UP;
        else if (newOpt == LevelSelectOption::LEVEL_SELECT_OPT_ONES_DOWN) newOpt = LevelSelectOption::LEVEL_SELECT_OPT_ONES_UP;
        else if (newOpt <= LevelSelectOption::LEVEL_SELECT_OPT_NONE) newOpt = LevelSelectOption::LEVEL_SELECT_OPT_PLAY;
        opt = (LevelSelectOption)newOpt;
    }
    if (InputPressed(InputButton::Right))
    {
        int newOpt = opt + 1;
        if (newOpt == LevelSelectOption::LEVEL_SELECT_OPT_TENS_DOWN) newOpt = LevelSelectOption::LEVEL_SELECT_OPT_ONES_UP;
        else if (newOpt == LevelSelectOption::LEVEL_SELECT_OPT_ONES_DOWN) newOpt = LevelSelectOption::LEVEL_SELECT_OPT_PLAY;
        else if (newOpt >= LevelSelectOption::LEVEL_SELECT_OPT_COUNT) newOpt = LevelSelectOption::LEVEL_SELECT_OPT_TENS_UP;
        opt = (LevelSelectOption)newOpt;
    }

    // Mouse.
    static float prevMouseX = 0.0f;
    static float prevMouseY = 0.0f;
    float mouseX = MouseX();
    float mouseY = MouseY();
    if (mouseX != prevMouseX || mouseY != prevMouseY)
    {
        bool found = false;
        if (mouseY >= LEVEL_SELECT_UI_UP_Y && mouseY < LEVEL_SELECT_UI_UP_Y + LEVEL_SELECT_UI_BLOCK_HEIGHT)
        {
            if (mouseX >= LEVEL_SELECT_UI_TENS_X && mouseX < LEVEL_SELECT_UI_TENS_X + LEVEL_SELECT_UI_BLOCK_WIDTH)
            {
                opt = LevelSelectOption::LEVEL_SELECT_OPT_TENS_UP;
                found = true;
            }
            else if (mouseX >= LEVEL_SELECT_UI_ONES_X && mouseX < LEVEL_SELECT_UI_ONES_X + LEVEL_SELECT_UI_BLOCK_WIDTH)
            {
                opt = LevelSelectOption::LEVEL_SELECT_OPT_ONES_UP;
                found = true;
            }
        }
        if (mouseY >= LEVEL_SELECT_UI_DOWN_Y && mouseY < LEVEL_SELECT_UI_DOWN_Y + LEVEL_SELECT_UI_BLOCK_HEIGHT)
        {
            if (mouseX >= LEVEL_SELECT_UI_TENS_X && mouseX < LEVEL_SELECT_UI_TENS_X + LEVEL_SELECT_UI_BLOCK_WIDTH)
            {
                opt = LevelSelectOption::LEVEL_SELECT_OPT_TENS_DOWN;
                found = true;
            }
            else if (mouseX >= LEVEL_SELECT_UI_ONES_X && mouseX < LEVEL_SELECT_UI_ONES_X + LEVEL_SELECT_UI_BLOCK_WIDTH)
            {
                opt = LevelSelectOption::LEVEL_SELECT_OPT_ONES_DOWN;
                found = true;
            }
        }
        if (mouseY >= LEVEL_SELECT_UI_PLAY_Y && mouseY < LEVEL_SELECT_UI_PLAY_Y + LEVEL_SELECT_UI_BLOCK_HEIGHT)
        {
            if (mouseX >= LEVEL_SELECT_UI_PLAY_X && mouseX < LEVEL_SELECT_UI_PLAY_X + LEVEL_SELECT_UI_BLOCK_WIDTH)
            {
                opt = LevelSelectOption::LEVEL_SELECT_OPT_PLAY;
                found = true;
            }
        }
        if (!found) opt = LevelSelectOption::LEVEL_SELECT_OPT_NONE;
    }
    prevMouseX = mouseX;
    prevMouseY = mouseY;

    // Handle select.
    if (InputPressed(InputButton::Up))
    {
        if (opt == LevelSelectOption::LEVEL_SELECT_OPT_TENS_UP || opt == LevelSelectOption::LEVEL_SELECT_OPT_TENS_DOWN)
        {
            numbersTens.num++;
            numbersTens.num %= 5;
        }
        else if (opt == LevelSelectOption::LEVEL_SELECT_OPT_ONES_UP || opt == LevelSelectOption::LEVEL_SELECT_OPT_ONES_DOWN)
        {
            numbersOnes.num++;
            numbersOnes.num %= 10;
        }
    }
    if (InputPressed(InputButton::Down))
    {
        if (opt == LevelSelectOption::LEVEL_SELECT_OPT_TENS_UP || opt == LevelSelectOption::LEVEL_SELECT_OPT_TENS_DOWN)
        {
            if (numbersTens.num > 0) numbersTens.num--;
            else numbersTens.num = 4;
        }
        else if (opt == LevelSelectOption::LEVEL_SELECT_OPT_ONES_UP || opt == LevelSelectOption::LEVEL_SELECT_OPT_ONES_DOWN)
        {
            if (numbersOnes.num > 0) numbersOnes.num--;
            else numbersOnes.num = 9;
        }
    }
    if (InputPressed(InputButton::Mouse))
    {
        switch (opt)
        {
            case LevelSelectOption::LEVEL_SELECT_OPT_TENS_UP:
                numbersTens.num++;
                numbersTens.num %= 5;
                break;
            case LevelSelectOption::LEVEL_SELECT_OPT_TENS_DOWN:
                if (numbersTens.num > 0) numbersTens.num--;
                else numbersTens.num = 4;
                break;
            case LevelSelectOption::LEVEL_SELECT_OPT_ONES_UP:
                numbersOnes.num++;
                numbersOnes.num %= 10;
                break;
            case LevelSelectOption::LEVEL_SELECT_OPT_ONES_DOWN:
                if (numbersOnes.num > 0) numbersOnes.num--;
                else numbersOnes.num = 9;
                break;
            default:
                break;
        }
    }
    if ((InputPressed(InputButton::Mouse) && opt == LevelSelectOption::LEVEL_SELECT_OPT_PLAY) || InputPressed(InputButton::Jump))
    {
        game.currScenarioNum = numbersTens.num * 10 + numbersOnes.num;
        game.Reload();
        Kill();
    }

}