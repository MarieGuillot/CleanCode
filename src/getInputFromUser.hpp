#pragma once

#include <iostream>
#include <limits>
#include <string>

// ask an input
template<typename T>
T getInputFromUser()
{
    T playerInput;
    while (!(std::cin >> playerInput)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "It's not the good type of input." << std::endl;
    }

    return playerInput;
}

// ask specifically a letter (and not all char)
char getLetterFromUser();