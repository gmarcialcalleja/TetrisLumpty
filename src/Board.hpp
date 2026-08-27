#pragma once
#include <vector>
#include "Tetromino.hpp"
#include "ShapeDatabase.hpp"
#include <memory>
#include <array>
class Board {
private:
    std::vector<std::vector<ShapeType>> board = std::vector(20, std::vector<ShapeType>(10, ShapeType::Empty));
public:
    std::vector<std::vector<ShapeType>> getBoardCopy() {return board;}
    int num_rows() {return static_cast<int>(board.size());}
    int num_cols() {return static_cast<int>(board.at(0).size());}
    void lock(const std::shared_ptr<Tetromino>& piece);
    bool isDropValid(const std::array<std::pair<int, int>, 4>& matrix, const std::pair<int,int> position);
    bool isValid(int y_next, int x_next);
    bool isMoveValid(const std::array<std::pair<int, int>, 4>& matrix, const std::pair<int,int> position, std::string move);
    bool isCWValid(const std::array<std::pair<int, int>, 4>& TetrisMatrix, const std::pair<int,int>& position);
};

//--------------------------------------------------------------------------------------------------------

bool Board::isDropValid(const std::array<std::pair<int, int>, 4>& matrix, const std::pair<int,int> position) {
    for(const auto& [first, second] : matrix) {
        int x_next = second + position.second;
        int y_next = first + 1 + position.first;
        if(!isValid(y_next, x_next)) return false;
    }
    return true;
}
bool Board::isValid(int y_next, int x_next) {
    
    if(x_next >= num_cols() || x_next < 0 || y_next >= num_rows() || board.at(y_next).at(x_next) != ShapeType::Empty) {
        return false;
    }
    return true;
}

bool Board::isMoveValid(const std::array<std::pair<int, int>, 4>& matrix, const std::pair<int,int> position, std::string move) {
    int counter = (move == "left") ? -1 : 1;
    for(const auto& [first, second] : matrix) {
        int x_next = second + position.second + counter;
        int y_next = first + position.first;
        if(!isValid(y_next, x_next)) return false;
    }
    return true;
}

bool Board::isCWValid(const std::array<std::pair<int, int>, 4>& TetrisMatrix, const std::pair<int,int>& position) {
    for(const auto& [first,second] : TetrisMatrix) {
        int x_next = second + position.second;
        int y_next = first + position.first;
        if(!isValid(y_next,x_next)) return false;
    }
    return true;
}

void Board::lock(const std::shared_ptr<Tetromino>& piece) {
    const auto& array = ShapeDatabase::getMatrix(piece->getType(), piece->getRotation());
    for(const auto& [y,x] : array) {
        board.at(y + piece->getPosition().first).at(x + piece->getPosition().second) = piece->getType();
    }
}