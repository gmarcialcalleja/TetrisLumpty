
#include <vector>
#include <array>
#include <iostream>
#include <memory>
#include <random>
#include <queue>
#include "ShapeDatabase.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"
#include "Factory.hpp"
#include "Game.hpp"


int main() {
    Game game;
    std::string command = "";
    while(command != "quit" && command != "exit") {
        std::cin >> command;
        if(command == "print") game.printBoard();
        else if(command == "n") game.tick();
        else if(command == "r") game.move("right");
        else if(command == "l") game.move("left");
        else if(command == "cw") game.rotateClockwise();
    }
    return 0;
}