#include "playAgain.hpp"

class Game {
public:
    Game(const std::string& name, std::function<void()> play)
        : _name(name), _play(play){};

    void               play() { playUntilThePlayerWantToStop(_play, true); };
    inline std::string getName() { return _name; };

private:
    const std::string     _name;
    std::function<void()> _play;
};