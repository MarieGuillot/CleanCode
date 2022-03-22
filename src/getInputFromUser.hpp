#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

// Utiliser un bool qui part défaut vaut false en paramètre et le faire passer à true si je veux une lettre ?

template<typename T>
T getInputFromUser()
{
    T playerInput;
    while (!(std::cin >> playerInput)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "It's not the good type of input." << std::endl;
    }
    if (std::is_same<T, char>::value) {
        if (!isalpha(playerInput)) {
            std::cout << "Give me a LETTER, please." << std::endl;
            return getInputFromUser<T>();
        }
    }
    return playerInput;
}
