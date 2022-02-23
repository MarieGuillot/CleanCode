#include "hangman.hpp"
#include <array>
#include <iostream>
#include <string>
#include "random.hpp"

std::string chooseARandomWord()
{
    constexpr size_t                                    numberOfWords = 4;
    static const std::array<std::string, numberOfWords> words         = {
        "Congratulation",
        "Answer",
        "Winner",
        "End",
    };

    const auto wordPosition = giveRandomIntegerNumber<size_t>(0, numberOfWords - 1);
    return words[wordPosition];
}

void playHangman()
{
    std::string myWord = chooseARandomWord();
    std::cout << myWord << std::endl;
}