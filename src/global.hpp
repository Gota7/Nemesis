#pragma once

#include <iostream>
#include <memory>
#include <raylib.h>

#ifdef DEBUG
    #define DBG_PRINT(x) do { std::cout << x << std::endl; } while (false)
#else
    #define DBG_PRINT(x) do {} while (false)
#endif

#define PTR std::unique_ptr
#define PTR_MAKE(T, x...) std::make_unique<T>(x)
#define VEC_CAST(vec) *(Vector2*)&vec

#define RES_WIDTH 1280
#define RES_HEIGHT 720
#define FPS 60
#define FRAME_TIME_DEFAULT 0.15f