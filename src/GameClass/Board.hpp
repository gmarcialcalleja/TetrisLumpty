#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <array>
#include <unordered_set>
#include "Tetromino.hpp"
#include "ShapeDatabase.hpp"
#include "./Observer/IObserver.hpp"
#include "./Observer/Subject.hpp"

class Board : public Subject{ 
private:
    std::vector<std::vector<ShapeType>> board = std::vector(20, std::vector<ShapeType>(10, ShapeType::Empty));
    std::vector<IObserver*> observer_vector;
public:
    //Subject stuff
    void notify(int numLines) override {for(const auto& observer_ptr : observer_vector) observer_ptr->onNotify(numLines);}
    void attach_observer(IObserver* observer) override {observer_vector.push_back(observer);}
    void detach_observer(IObserver* observer) override {std::erase(observer_vector, observer);}

    std::vector<std::vector<ShapeType>> getBoardCopy() {return board;}
    int num_rows() {return static_cast<int>(board.size());}
    int num_cols() {return static_cast<int>(board.at(0).size());}
    void lock(const std::shared_ptr<Tetromino>& piece);
    
    bool isValid(int y_next, int x_next);
    bool isCWValid(const std::shared_ptr<Tetromino>& piece);
    bool isCWValid(const std::shared_ptr<Tetromino>& piece, const std::pair<int,int>& position);
    bool isRotateValid(const std::shared_ptr<Tetromino>& piece, const std::pair<int,int>& position, const std::string& rotation_type);
    bool isMoveValid(const std::shared_ptr<Tetromino>& piece, std::string move);
    bool isDropValid(const std::shared_ptr<Tetromino>& piece);

    void clear_if_fill(int x_pos, const std::array<std::pair<int, int>, 4>& TetrisMatrix);
    void clear_rows(const std::vector<int>& rows);
    void reset() {board = std::vector(20, std::vector<ShapeType>(10, ShapeType::Empty));}
   

    
    
};

//--------------------------------------------------------------------------------------------------------
void Board::clear_if_fill(int x_pos, const std::array<std::pair<int, int>, 4>& TetrisMatrix) {
    auto isFilled = [&](int x) ->bool {
        for(const auto& shape : board.at(x)) //js checks a whole row
            if(shape == ShapeType::Empty) return false;
        return true;
    };
    std::unordered_set<int> visited;
    std::vector<int> filled_positions;
    for(const auto& [x_shape, y_shape] : TetrisMatrix ) {
        int final_x = x_pos + x_shape;
        if(!visited.count(final_x)) {
            if(isFilled(final_x)) 
                filled_positions.push_back(final_x);
            
            visited.insert(final_x);
        }
    }
    std::sort(filled_positions.begin(), filled_positions.end());
    clear_rows(filled_positions);
    if(filled_positions.size()) notify(static_cast<int>(filled_positions.size()));
}

void Board::clear_rows(const std::vector<int>& rows) {
    for(const int& x : rows) {
        for(int i = x; i > 0; i--) 
            board.at(i) = board.at(i-1);
        for(auto& shape : board.at(0)) 
            shape = ShapeType::Empty; 
    }

}

bool Board::isDropValid(const std::shared_ptr<Tetromino>& piece) {
    auto TetrisMatrix = ShapeDatabase::getMatrix(piece->getType(), piece->getRotation());
    const std::pair<int,int>& position = piece->getPosition();
    for(const auto& [first, second] : TetrisMatrix) {
        int x_next = second + position.second;
        int y_next = first + 1 + position.first;
        if(!isValid(y_next, x_next)) return false;
    }
    return true;
}
bool Board::isValid(int y_next, int x_next) {
    if(x_next >= num_cols() || x_next < 0 || y_next >= num_rows() || y_next < 0 || board.at(y_next).at(x_next) != ShapeType::Empty) {
        return false;
    }
    return true;
}

bool Board::isMoveValid(const std::shared_ptr<Tetromino>& piece, std::string move) {
    auto TetrisMatrix = ShapeDatabase::getMatrix(piece->getType(), piece->getRotation());
    const std::pair<int,int>& position = piece->getPosition();
    int counter = (move == "left") ? -1 : 1;
    for(const auto& [first, second] : TetrisMatrix) {
        int x_next = second + position.second + counter;
        int y_next = first + position.first;
        if(!isValid(y_next, x_next)) return false;
    }
    return true;
}


bool Board::isCWValid(const std::shared_ptr<Tetromino>& piece) {
    auto TetrisMatrix = ShapeDatabase::getMatrix(piece->getType(), (piece->getRotation()+1)%4);
    const std::pair<int,int>& position = piece->getPosition();
    for(const auto& [first,second] : TetrisMatrix) {
        int x_next = second + position.second;
        int y_next = first + position.first;
        if(!isValid(y_next,x_next)) return false;
    }
    return true;
}
bool Board::isCWValid(const std::shared_ptr<Tetromino>& piece, const std::pair<int,int>& position) {
    auto TetrisMatrix = ShapeDatabase::getMatrix(piece->getType(), (piece->getRotation()+1)%4);
    for(const auto& [first,second] : TetrisMatrix) {
        int x_next = second + position.second;
        int y_next = first + position.first;
        if(!isValid(y_next,x_next)) return false;
    }
    return true;
}

bool Board::isRotateValid(const std::shared_ptr<Tetromino>& piece, const std::pair<int,int>& position, const std::string& rotation_type) {
    int offset = (rotation_type == "CW") ? 1 : 3;
    auto TetrisMatrix = ShapeDatabase::getMatrix(piece->getType(), (piece->getRotation()+offset)%4);
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