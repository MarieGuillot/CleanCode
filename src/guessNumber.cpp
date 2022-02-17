#include "guessNumber.hpp"
#include <chrono>
#include <functional>
#include <random>

guessNumber::guessNumber()
{
    pickANumber();
}

void guessNumber::pickANumber()
{
    unsigned                           seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937                       generator(seed);
    std::uniform_int_distribution<int> uniformIntDistribution(0, 100);
    randomNumber = uniformIntDistribution(generator);
}

bool guessNumber::tryNumber(const int guess, std::string& answer)
{
    if (guess < randomNumber) {
        answer = "Greater";
        return false;
    }
    else if (guess > randomNumber) {
        answer = "Smaller";
        return false;
    }
    else {
        answer = "Congrats, you won!";
        return true;
    }
}

int guessNumber::getIntFromUser()
{
    int playerNumber;
    std::cout << "Give me a number" << std::endl;
    while (!(std::cin >> playerNumber)) {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Give me a NUMBER, please." << std::endl;
    }
    return playerNumber;
}

void guessNumber::play()
{
    bool        game = true;
    int         playerNumber;
    std::string answer;

    while (game) {
        bool win = false;
        pickANumber();
        std::cout << "I picked a number between 0 and 100" << std::endl;
        while (!win) {
            playerNumber = getIntFromUser();
            win          = tryNumber(playerNumber, answer);
            std::cout << answer << std::endl;
        }
        std::string doesThePlayerWannaPlay;
        std::cout << "Do you want to play again ? yes/no" << std::endl;
        std::cin >> doesThePlayerWannaPlay;
        if (doesThePlayerWannaPlay == "no") {
            game = false;
        }
    }
}