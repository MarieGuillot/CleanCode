#pragma once

#include <functional>

void playUntilThePlayerWantsToStop(std::function<void()> playFunction, bool sameGame); //sameGame = true to play the same game, false to change game
bool doYouWantToPlayAgain(bool sameGame);