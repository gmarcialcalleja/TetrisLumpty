#pragma once
#include <iostream>
class ScoreTracker : public IObserver {
private:
    int score;
public:
    ScoreTracker():score(0) {};
    void onNotify(int numLines) override {
        if(numLines == 1) score += 100;
        if(numLines == 2) score += 300;
        if(numLines == 3) score += 500;
        if(numLines == 4) score += 800;// keep track of this in my get scorer
        std::cout << score << std::endl;
    };

    int getScore() {return score;}
};