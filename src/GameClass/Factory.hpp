#pragma once
#include "Tetromino.hpp"
#include <random>
#include <memory>
#include <stack>
#include <vector>
class TetrisFactory {
private:
    std::stack<std::shared_ptr<Tetromino>> stack;
    std::vector<std::shared_ptr<Tetromino>> vec;
    int size;
    std::shared_ptr<Tetromino> held_piece;
public:
    TetrisFactory();
    void fill_stack();
    bool isEmpty() {return stack.empty();}
    std::shared_ptr<Tetromino> load_next_piece();
    void hold(std::shared_ptr<Tetromino> piece);
    std::shared_ptr<Tetromino> top() {return stack.top();}
    const std::shared_ptr<Tetromino>& show_held_piece() {return held_piece;}
    
};

//------------------------------------------------------------------------------------------------
void TetrisFactory::hold(std::shared_ptr<Tetromino> piece) {
    if(held_piece) stack.push(held_piece);;
    held_piece = piece;
}



TetrisFactory::TetrisFactory() {
    size = 7;
    vec.push_back(nullptr);
    for(int i = 1; i <= size; i++) {
        vec.push_back(std::make_shared<Tetromino>(Tetromino(i)));
    }
    fill_stack();
    
}
void TetrisFactory::fill_stack() {
    // create the set
    if(stack.size() == size) return;
    std::vector<int> set(size+1);
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, size);//make sure to remember to change this
    while(stack.size() < size) {
        int type = distrib(gen);
        if(set.at(type)) continue;
        stack.push(vec.at(type));
        set.at(type) = 1;
    }
}

std::shared_ptr<Tetromino> TetrisFactory::load_next_piece() {
    if(stack.empty()) fill_stack();
    std::shared_ptr<Tetromino> piece = stack.top();
    stack.pop();
    return piece;
}