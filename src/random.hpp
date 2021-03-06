#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <random>

// return a number integer number (as it is a template, you can ask for a size_t)
template<typename T>
T giveRandomIntegerNumber(T min, T max)
{
    unsigned                           seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937                       generator(seed);
    int                                intMin = int(min);
    int                                intMax = int(max);
    std::uniform_int_distribution<int> uniformIntDistribution(intMin, intMax);
    return T(uniformIntDistribution(generator));
}