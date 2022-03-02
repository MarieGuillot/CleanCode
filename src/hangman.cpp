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
        word += "_";
        numberOfLetters--;
    }
    return word;
}

void showWithSpace(std::string word)
{
    for (const char word_letter : word) {
        std::cout << word_letter << " ";
    }
    std::cout << std::endl;
}

bool isLetterInTheWord(char letter, std::string word, std::vector<int>& positionsOfLetter)
{
    bool has_found      = false;
    int  letterPosition = 0;
    for (const char word_letter : word) {
        if (word_letter == letter || word_letter == toupper(letter) || toupper(word_letter) == letter) {
            positionsOfLetter.push_back(letterPosition);
            has_found = true;
        }
        letterPosition++;
    }
    return has_found;
}

std::string replaceWithGoodLetters(std::string solutionWord, std::string word, std::vector<int> positionsOfLetter)
{
    for (const auto& location : positionsOfLetter) {
        word[location] = solutionWord[location];
    }
    return word;
}

void hangmanConclusion(const uint playerLives, const std::string& solutionWord)
{
    if (playerLives > 0) {
        std::cout << "You win !";
    }
    else {
        std::cout << "You die!";
    }
    std::cout << "The word was : " << solutionWord << " " << std::endl;
}

void playHangman()
{
    uint        playerLives    = 8;
    std::string solutionWord   = chooseARandomWord();
    std::string alreadyGuessed = wordMadeOfUnderscore(solutionWord.length());
    showWithSpace(alreadyGuessed);

    while (solutionWord != alreadyGuessed && playerLives > 0) {
        std::cout << "You have " << playerLives << " lives." << std::endl;
        std::cout << "Give me one letter (only the first letter will be used)" << std::endl;
        char             playerLetter = getOneLetterFromUser();
        std::vector<int> positionsOfLetter;
        if (isLetterInTheWord(playerLetter, solutionWord, positionsOfLetter)) {
            alreadyGuessed = replaceWithGoodLetters(solutionWord, alreadyGuessed, positionsOfLetter);
        }
        else {
            playerLives--;
            std::cout << "The letter " << playerLetter << " is not in the word." << std::endl;
        }
        showWithSpace(alreadyGuessed);
    }

    hangmanConclusion(playerLives, solutionWord);
}