#pragma once

#include "playAgain.hpp"

// this class represent a game, with its name and the function that must be called to play the game
class Game {
public:
    Game(const std::string& name, std::function<void()> play)
        : _name(name), _play(play){};

    void               play() { playUntilThePlayerWantsToStop(_play, true); };
    inline std::string getName() { return _name; };

private:
    const std::string     _name;
    std::function<void()> _play;
};