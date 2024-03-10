#pragma once

#include "global.hpp"
#include <map>

enum class InputButton
{
    Left,
    Right,
    Up,
    Down,
    Jump,
    Run,
    Mouse,
    Pause
};

inline std::map<InputButton, int> KEYMAP =
{
    { InputButton::Left, KEY_LEFT },
    { InputButton::Right, KEY_RIGHT },
    { InputButton::Up, KEY_UP },
    { InputButton::Down, KEY_DOWN },
    { InputButton::Jump, KEY_Z },
    { InputButton::Run, KEY_X },
    { InputButton::Mouse, MOUSE_LEFT_BUTTON },
    { InputButton::Pause, KEY_ESCAPE },
};

// Have to make this bc web is stupid and doesn't work I hate you.
inline std::map<InputButton, bool> BUTTON_WAS_DOWN;

inline bool InputDown(InputButton button)
{
    if (button == InputButton::Mouse) return IsMouseButtonDown(KEYMAP[button]);
    else return IsKeyDown(KEYMAP[button]);
}

inline bool InputUp(InputButton button)
{
    if (button == InputButton::Mouse) return IsMouseButtonUp(KEYMAP[button]);
    else return IsKeyUp(KEYMAP[button]);
}

inline bool InputPressed(InputButton button)
{
    return InputDown(button) && !BUTTON_WAS_DOWN[button];
}

inline bool InputReleased(InputButton button)
{
    return InputUp(button) && BUTTON_WAS_DOWN[button];
}

inline void InputUpdate()
{
    for (auto& entry : KEYMAP)
    {
        BUTTON_WAS_DOWN[entry.first] = InputDown(entry.first);
    }
}

inline float MouseX()
{
    return GetMouseX() * ((float)RES_WIDTH / GetScreenWidth());
}

inline float MouseY()
{
    return GetMouseY() * ((float)RES_HEIGHT / GetScreenHeight());
}