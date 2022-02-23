#include "hangman.hpp"
#include <array>
#include <cctype>
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
    return words.at(wordPosition);
}

std::string getOneLetterFromUser()
{
    std::string playerLetter = "a";
    std::cout << "Give me a letter" << std::endl;
    while (!(std::cin >> playerLetter)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Give me a letter, please." << std::endl;
    }
    if (playerLetter.length() > 1) {
        std::cout << "You can try only one letter." << std::endl;
        return getOneLetterFromUser();
    }
    if (!isalpha(int(playerLetter.at(0)))) {
        std::cout << "Give me a letter, please." << std::endl;
        return getOneLetterFromUser();
    }
    return playerLetter;
}

void playHangman()
{
    std::string solutionWord = chooseARandomWord();
    std::cout << solutionWord << std::endl;
    std::string playerLetter = getOneLetterFromUser();
    std::cout << playerLetter << std::endl;
}