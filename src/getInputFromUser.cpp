#include "getInputFromUser.hpp"

char getLetterFromUser()
{
    char letter = getInputFromUser<char>();
    while (!isalpha(letter)) {
        std::cout << "Give me a LETTER, please." << std::endl;
        letter = getLetterFromUser();
    }
    return letter;
}