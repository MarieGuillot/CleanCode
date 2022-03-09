#include "playAgain.hpp"
#include <functional>
#include <iostream>

bool playAgainGame()
{
    std::string doesThePlayerWannaPlay;
    std::cout << "Do you want to play again ? yes/no" << std::endl;
    std::cin >> doesThePlayerWannaPlay;
    if (doesThePlayerWannaPlay == "no") {
        return false;
    }
    else if (doesThePlayerWannaPlay != "yes") {
        return playAgainGame();
    }
    return true;
}

void playUntilThePlayerWantToStop(std::function<void()> playFunction)
{
    bool game = true;

    while (game) {
        playFunction();
        game = playAgainGame();
    }
}