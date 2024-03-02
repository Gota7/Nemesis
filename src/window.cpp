#include "window.hpp"

#include <math.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576
#define RES_WIDTH 1280
#define RES_HEIGHT 720

Window::Window()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Complementary Nemesis");
    SetWindowMonitor(0);
    SetTargetFPS(60);
    SetWindowMinSize(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    tex = LoadRenderTexture(RES_WIDTH, RES_HEIGHT);
}

void Window::Run(const WindowFunc& drawFunc, const WindowFunc& updateFunc)
{
    while (!WindowShouldClose())
    {

        // Fix wonky window sizes.
        float width = GetRenderWidth();
        float height = GetRenderHeight();
        if (!IsWindowFullscreen() && !IsWindowMaximized() && width / height != (float)RES_WIDTH / RES_HEIGHT)
        {
            float oldHeight = height;
            height = RES_HEIGHT * width / RES_WIDTH;
            SetWindowSize((int)width, (int)height);
            DBG_PRINT("Resized invalid size " << (int)width << "x" << (int)oldHeight << " to " << (int)width << "x" << (int)height);
        }

        // Render target.
        BeginTextureMode(tex);
        ClearBackground(BLACK);
        drawFunc();
        EndTextureMode();

        // Main window.
        BeginDrawing();
        DrawTexturePro(
            tex.texture,
            { 0.0f, 0.0f, (float)tex.texture.width, (float)-tex.texture.height },
            { 0.0f, 0.0f, width, height },
            { 0.0f, 0.0f },
            0.0f,
            WHITE
        );
        EndDrawing();

        // Updates.
        updateFunc();

    }
}

Window::~Window()
{
    UnloadRenderTexture(tex);
    CloseWindow();
}