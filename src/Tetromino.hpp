#pragma once
#include "ShapeDatabase.hpp"
#include <vector>
#include <string>
#include <array>

class Tetromino { 
private:
    ShapeType type;
    int rotation; 
    std::pair<int, int> position;
public:
    Tetromino(int type_) : type(static_cast<ShapeType>(type_)), rotation(0), position({0,4}) {}
    const ShapeType& getType() {return type;}
    const int& getRotation() {return rotation;}
    const std::pair<int,int>& getPosition() {return position;}
    void down() {position.first++;}
    
    void move(std::string move);
    void rotateClockwise();
    void default_state();
    //send next state
};
//--------------------------------------------------------------------------------------------------
void Tetromino::move(std::string move) {
    if(move == "right") position.second++;
    else position.second--;
}
void Tetromino::rotateClockwise() {
    rotation = (rotation + 1) % 4;
}
void Tetromino::default_state() {
    rotation = 0;
    position = {0,4};
}