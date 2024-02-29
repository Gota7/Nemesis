#pragma once

#include <iostream>
#include <memory>
#include <raylib.h>

#define DEBUG 1

#ifdef DEBUG
    #define DBG_PRINT(x) do { std::cout << x << std::endl; } while (false)
#elif
    #define NDEBUG 1
    #define DBG_PRINT(x) do {} while (false)
#endif

#define PTR std::unique_ptr
#define PTR_MAKE(T, x...) std::make_unique<T>(x)
#define VEC_CAST(vec) *(Vector2*)&vec