#include "hangman.hpp"
#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <string>
#include "getInputFromUser.hpp"
#include "random.hpp"

std::string wordMadeOfUnderscore(int numberOfLetters)
{
    std::string word = "";
    while (numberOfLetters != 0) {
        word += "_";
        numberOfLetters--;
    }
    return word;
}

class hangmanWords {
public:
    explicit hangmanWords(const std::string& word)
        : _solutionWord(word), _alreadyGuessed(wordMadeOfUnderscore(_solutionWord.length()))
    {
    }

    inline bool found() { return _solutionWord == _alreadyGuessed; }
    void        replaceGuessedWordWithGoodLetters(std::vector<int> positionsOfLetter)
    {
        for (const auto& location : positionsOfLetter) {
            _alreadyGuessed[location] = _solutionWord[location];
        }
    }
    void showGuessedWord()
    {
        for (const char word_letter : _alreadyGuessed) {
            std::cout << word_letter << " ";
        }
        std::cout << std::endl;
    }

    inline const std::string& solution() const { return _solutionWord; }

private:
    std::string _solutionWord;
    std::string _alreadyGuessed;
};

std::string
    chooseARandomWord()
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

void showNumberOfLives(int numberOfLives)
{
    std::cout << "You have " << numberOfLives << " lives." << std::endl;
}

bool playerIsAlive(int numberOfLives)
{
    return numberOfLives > 0;
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
    if (isLetterInTheWord(static_cast<char>(toupper(letter)), goodLetters) || isLetterInTheWord(static_cast<char>(toupper(letter)), badLetters)) {
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

void hangmanConclusion(const uint playerLives, const std::string& solutionWord)
{
    if (playerIsAlive(playerLives)) {
        std::cout << "You win!";
    }
    else {
        std::cout << "You die!";
    }
    std::cout << " The word was: " << solutionWord << " " << std::endl;
}

void playHangman()
{
    uint         playerLives = 8;
    hangmanWords hangmanWords(chooseARandomWord());
    hangmanWords.showGuessedWord();
    std::string goodLetters = "";
    std::string badLetters  = "";

    while (!hangmanWords.found() && playerIsAlive(playerLives)) {
        showNumberOfLives(playerLives);
        char playerLetter = [&]() {
            while (true) {
                std::cout << "Give me one letter (only the first letter will be used)" << std::endl;
                const char letter = getLetterFromUser();
                if (!isLetterAlreadyTried(letter, goodLetters, badLetters)) {
                    return letter;
                }
            };
        }();

        std::vector<int> positionsOfLetter;
        if (isLetterInTheWordAndWhere(playerLetter, hangmanWords.solution(), positionsOfLetter)) {
            goodLetters += toupper(playerLetter);
            hangmanWords.replaceGuessedWordWithGoodLetters(positionsOfLetter);
        }
        else {
            badLetters += toupper(playerLetter);
            playerLives--;
            std::cout << "The letter " << playerLetter << " is not in the word." << std::endl;
        }
        hangmanWords.showGuessedWord();
    }

    hangmanConclusion(playerLives, hangmanWords.solution());
}
