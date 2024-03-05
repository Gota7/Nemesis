#pragma once

#include <random>

// Make a new random number inclusively.
inline std::size_t RandomNum(std::size_t min, std::size_t max)
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    return std::uniform_int_distribution(min, max)(rng);
}