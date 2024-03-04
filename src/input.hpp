#pragma once

#include "global.hpp"
#include <map>

enum class InputButton
{
    Left,
    Right,
    Jump,
    Run
};

inline std::map<InputButton, int> KEYMAP =
{
    { InputButton::Left, KEY_LEFT },
    { InputButton::Right, KEY_RIGHT },
    { InputButton::Jump, KEY_Z },
    { InputButton::Run, KEY_X },
};

inline bool InputDown(InputButton button)
{
    return IsKeyDown(KEYMAP[button]);
}

inline bool InputUp(InputButton button)
{
    return IsKeyUp(KEYMAP[button]);
}

inline bool InputPressed(InputButton button)
{
    return IsKeyPressed(KEYMAP[button]);
}

inline bool InputReleased(InputButton button)
{
    return IsKeyReleased(KEYMAP[button]);
}

inline float MouseX()
{
    return GetMouseX() * ((float)RES_WIDTH / GetScreenWidth());
}

inline float MouseY()
{
    return GetMouseY() * ((float)RES_HEIGHT / GetScreenHeight());
}