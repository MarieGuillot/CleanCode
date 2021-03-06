#include "playAgain.hpp"
#include <functional>
#include <iostream>

bool doYouWantToPlayAgain(bool sameGame)
{
    std::string doesThePlayerWannaPlay;
    if (sameGame) {
        std::cout << "Do you want to play again ? yes/no" << std::endl;
    }
    else {
        std::cout << "Do you want to play to another game ? yes/no" << std::endl;
    }
    std::cin >> doesThePlayerWannaPlay;
    if (doesThePlayerWannaPlay == "no") {
        return false;
    }
    else if (doesThePlayerWannaPlay != "yes") { // ask again if the input is not "yes" or "no"
        return doYouWantToPlayAgain(sameGame);
    }
    return true;
}

void playUntilThePlayerWantsToStop(std::function<void()> playFunction, bool sameGame)
{
    bool game = true;

    while (game) {
        playFunction();
        game = doYouWantToPlayAgain(sameGame);
    }
}