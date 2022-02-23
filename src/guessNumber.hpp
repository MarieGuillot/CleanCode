#include <iostream>
#include "random.hpp"

class guessNumber {
private:
    int randomNumber;

public:
    guessNumber();
    void pickANumber();
    int  getIntFromUser();
    bool tryNumber(int guess, std::string& answer) const;
    void play();
};