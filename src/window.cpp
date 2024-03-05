#include "window.hpp"

#include "input.hpp"
#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif
#include <math.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

Window::Window()
{
#ifdef PLATFORM_WEB
    InitWindow(RES_WIDTH, RES_HEIGHT, "Complementary Nemesis");
#else
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Complementary Nemesis");
#endif
#ifdef NDEBUG
    SetExitKey(0);
#endif
    SetWindowMonitor(0);
#ifndef PLATFORM_WEB
    SetTargetFPS(FPS);
    SetWindowMinSize(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    tex = LoadRenderTexture(RES_WIDTH, RES_HEIGHT);
#endif
}

void WindowDoUpdateDesktop(Window& window, const WindowFunc& drawFunc, const WindowFunc& updateFunc)
{
    // Fix wonky window sizes.
    float width = GetRenderWidth();
    float height = GetRenderHeight();
    if (!IsWindowFullscreen() && !IsWindowMaximized() && width / height != (float)RES_WIDTH / RES_HEIGHT)
    {
#ifdef DEBUG
        float oldHeight = height;
#endif
        height = RES_HEIGHT * width / RES_WIDTH;
        SetWindowSize((int)width, (int)height);
        DBG_PRINT("Resized invalid size " << (int)width << "x" << (int)oldHeight << " to " << (int)width << "x" << (int)height);
    }

    // Render target.
    BeginTextureMode(window.tex);
    ClearBackground(BLACK);
    drawFunc();
    EndTextureMode();

    // Main window.
    BeginDrawing();
    DrawTexturePro(
        window.tex.texture,
        { 0.0f, 0.0f, (float)window.tex.texture.width, (float)-window.tex.texture.height },
        { 0.0f, 0.0f, width, height },
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );
    EndDrawing();

    // Updates.
    updateFunc();
    InputUpdate();

}

void WindowDoUpdateWeb(Window&, const WindowFunc& drawFunc, const WindowFunc& updateFunc)
{

    // Main window.
    BeginDrawing();
    ClearBackground(BLACK);
    drawFunc();
    EndDrawing();

    // Updates.
    updateFunc();
    InputUpdate();

}

#ifdef PLATFORM_WEB
static Window* WINDOW;
static WindowFunc DRAWFUNC, UPDATEFUNC;
void WindowDoUpdateEmscripten()
{
    WindowDoUpdateWeb(*WINDOW, DRAWFUNC, UPDATEFUNC);
}
#endif

void Window::Run(const WindowFunc& drawFunc, const WindowFunc& updateFunc)
{
#ifdef PLATFORM_WEB
    WINDOW = this;
    DRAWFUNC = drawFunc;
    UPDATEFUNC = updateFunc;
    emscripten_set_main_loop(WindowDoUpdateEmscripten, FPS, 1);
#else
    while (!WindowShouldClose())
    {
        WindowDoUpdateDesktop(*this, drawFunc, updateFunc);
    }
#endif
}

Window::~Window()
{
    UnloadRenderTexture(tex);
    CloseWindow();
}