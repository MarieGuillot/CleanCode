#include "menu.hpp"

void menu()
{
    Game hangman("Hangman", &playHangman);
    Game guessNumber("Guess a number", &playGuessANumber);

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
