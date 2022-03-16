#include <iostream>
#include <vector>
#include "game.hpp"
#include "getInputFromUser.hpp"
#include "guessNumber.hpp"
#include "hangman.hpp"
#include "playAgain.hpp"

void menu()
{
    Game hangman("Hangman", playHangman);
    Game guessNumber("Guess a number", playGuessANumber);

    std::vector<Game> games;
    games.push_back(hangman);
    games.push_back(guessNumber);

    std::cout << "Select the game you want to play." << std::endl;
    for (size_t index = 0; index < games.size(); index++) {
        std::cout << index << " : " << games[index].getName() << std::endl;
    }
    std::cout << "^C : quit" << std::endl;

    const auto gameWished = getInputFromUser<size_t>();
    if (gameWished < games.size()) {
        games[gameWished].play();
    }

    std::cout << "Maybe we can try something else." << std::endl;
}

int main()
{
    playUntilThePlayerWantToStop(menu, false);

    // bool wantToPlay = true;
    // while (wantToPlay) {
    //     std::cout << "Select the game you want to play." << std::endl;
    //     for (size_t index = 0; index < games.size(); index++) {
    //         std::cout << index << " : " << games[index].getName() << std::endl;
    //     }
    //     std::cout << "^C : quit" << std::endl;

    //     const auto gameWished = getInputFromUser<size_t>();
    //     if (gameWished < games.size()) {
    //         games[gameWished].play();
    //     }

    //     std::cout << "Maybe we can try something else." << std::endl;
    //     wantToPlay = doYouWantToPlayAgain();
}
