#include "menu.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "connect4.hpp"
#include "game.hpp"
#include "getInputFromUser.hpp"
#include "guessNumber.hpp"
#include "hangman.hpp"
#include "noughtsAndCrosses.hpp"
#include "playAgain.hpp"

// show the menu (games in the vector games), and call the game that you choose
void menu()
{
    Game hangman("Hangman", &playHangman);
    Game guessNumber("Guess a number", &playGuessANumber);
    Game NoughtsAndCrosses("Noughts and crosses", &playNoughtsAndCrosses);
    Game connect4("Connect 4", &playConnect4);

    std::vector<Game> games;
    games.push_back(hangman);
    games.push_back(guessNumber);
    games.push_back(NoughtsAndCrosses);
    games.push_back(connect4);

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
