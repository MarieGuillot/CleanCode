#include "guessNumber.hpp"

bool tryNumber(const int guess, const int solution, std::string& answer)
{
    if (guess < solution) {
        answer = "Greater";
        return false;
    }
    else if (guess > solution) {
        answer = "Smaller";
        return false;
    }
    else {
        answer = "Congrats, you won!";
        return true;
    }
}

void playGuessANumber()
{
    int randomNumber = giveRandomIntegerNumber(0, 100);
    std::cout << "I picked a number between 0 and 100" << std::endl;
    bool win = false;
    while (!win) {
        std::cout << "Give me a number" << std::endl;
        int playerNumber = getInputFromUser<int>();
        if (playerNumber < 0 || playerNumber > 100) {
            std::cout << "Between 0 and 100 I said." << std::endl;
        }
        std::string answer;
        win = tryNumber(playerNumber, randomNumber, answer);
        std::cout << answer << std::endl;
    }
}
