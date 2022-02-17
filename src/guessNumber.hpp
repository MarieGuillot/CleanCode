#include <iostream>

class guessNumber {
private:
    int randomNumber;

public:
    guessNumber();
    void pickANumber();
    int  getIntFromUser();
    bool tryNumber(const int guess, std::string& answer);
    void play();
};