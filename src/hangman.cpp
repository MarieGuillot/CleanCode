#include "hangman.hpp"
#include <algorithm>
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

char getOneLetterFromUser()
{
    char playerLetter = 'a';
    while (!(std::cin >> playerLetter)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Give me one letter, please." << std::endl;
    }
    if (!isalpha(playerLetter)) {
        std::cout << "Give me a LETTER, please." << std::endl;
        return getOneLetterFromUser();
    }
    return playerLetter;
}

std::string wordMadeOfUnderscore(int numberOfLetters)
{
    std::string word = "";
    while (numberOfLetters != 0) {
        word += "_ ";
        numberOfLetters--;
    }
    return word;
}

bool isLetterInTheWord(char letter, std::string word)
{
    bool             has_found = false;
    std::vector<int> positionsOfLetter;
    int              letterPosition = 0;
    for (const char word_letter : word) {
        if (word_letter == letter) {
            positionsOfLetter.push_back(letterPosition);
            has_found = true;
        }
        letterPosition++;
    }
    for (const auto& value : positionsOfLetter) {
        std::cout << value << "\n";
    }
    return has_found;
}

void playHangman()
{
    std::string solutionWord = chooseARandomWord();
    std::cout << solutionWord << std::endl;
    std::cout << "Give me one letter (only the first letter will be used)" << std::endl;
    char playerLetter = getOneLetterFromUser();
    std::cout << playerLetter << std::endl;
    std::string alreadyGuessed = wordMadeOfUnderscore(solutionWord.length());
    std::cout << alreadyGuessed << std::endl;
    std::cout << isLetterInTheWord(playerLetter, solutionWord) << std::endl;
}