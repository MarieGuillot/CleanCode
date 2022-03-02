#include "hangman.hpp"
#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <string>
#include "getInputFromUser.hpp"
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

bool isLetterInTheWordAndWhere(char letter, std::string word, std::vector<int>& positionsOfLetter)
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

bool isLetterInTheWord(char letter, const std::string& word)
{
    return std::any_of(word.begin(), word.end(), [&](char word_letter) {
        return word_letter == letter;
    });
}

bool isLetterAlreadyTried(char letter, const std::string& goodLetters, const std::string& badLetters)
{
    if (isLetterInTheWord(letter, goodLetters) || isLetterInTheWord(letter, badLetters)) {
        std::cout << "You have already tried the letter " << letter << ".";
        if (!badLetters.empty()) {
            std::cout << " Bad letters tried : " << badLetters << ".";
        }
        if (!goodLetters.empty()) {
            std::cout << " Good letters found : " << goodLetters << ".";
        }
        std::cout << std::endl;

        return true;
    }
    return false;
}

std::string replaceWithGoodLetters(const std::string& solutionWord, std::string word, std::vector<int> positionsOfLetter)
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
    std::string goodLetters = "";
    std::string badLetters  = "";

    while (solutionWord != alreadyGuessed && playerLives > 0) {
        std::cout << "You have " << playerLives << " lives." << std::endl;
        char playerLetter;

        do {
            std::cout << "Give me one letter (only the first letter will be used)" << std::endl;
            playerLetter = getInputFromUser<char>();
        } while (isLetterAlreadyTried(playerLetter, goodLetters, badLetters));
        std::vector<int> positionsOfLetter;
        if (isLetterInTheWordAndWhere(playerLetter, solutionWord, positionsOfLetter)) {
            goodLetters += playerLetter;
            alreadyGuessed = replaceWithGoodLetters(solutionWord, alreadyGuessed, positionsOfLetter);
        }
        else {
            badLetters += playerLetter;
            playerLives--;
            std::cout << "The letter " << playerLetter << " is not in the word." << std::endl;
        }
        showWithSpace(alreadyGuessed);
    }

    hangmanConclusion(playerLives, solutionWord);
}