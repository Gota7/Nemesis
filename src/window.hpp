#pragma once

#include <functional>
#include <raylib.h>
#include "global.hpp"

using WindowFunc = std::function<void()>;

// Main window.
struct Window
{
    RenderTexture2D tex;

    // Create a new window.
    Window();

    // Run.
    void Run(const WindowFunc& drawFunc, const WindowFunc& updateFunc);

    // Destroy the window.
    ~Window();

};