#pragma once

#include <functional>

// play a game, then ask if the player wants to continue, and repeat until he wants to stop
void playUntilThePlayerWantsToStop(std::function<void()> playFunction, bool sameGame); //sameGame = true to play the same game, false to change game
// ask the player if he wants to play to the same game (param true) or to another game (param false)
bool doYouWantToPlayAgain(bool sameGame);