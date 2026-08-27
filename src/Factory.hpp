#pragma once
#include "Tetromino.hpp"
#include <random>
#include <memory>
#include <queue>
#include <vector>
class TetrisFactory {
private:
    std::queue<std::shared_ptr<Tetromino>> q;
    std::vector<std::shared_ptr<Tetromino>> vec;
    int size;
public:
    TetrisFactory();
    void fill_queue();
    bool isEmpty() {return q.empty();}
    std::shared_ptr<Tetromino> load_next_piece();
};

//------------------------------------------------------------------------------------------------
TetrisFactory::TetrisFactory() {
    //somehow randomize/ scramble different permutations 
    //hash set and insert into a queue;
    size = 7;
    vec.push_back(nullptr);
    for(int i = 1; i <= size; i++) {
        vec.push_back(std::make_shared<Tetromino>(Tetromino(i)));
    }
    fill_queue();
    
}
void TetrisFactory::fill_queue() {
    // create the set
    if(q.size() == size) return;
    std::vector<int> set(size+1);
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(1, size);//make sure to remember to change this
    while(q.size() < size) {
        int type = distrib(gen);
        if(set.at(type)) continue;
        q.push(vec.at(type));
        set.at(type) = 1;
    }
}

std::shared_ptr<Tetromino> TetrisFactory::load_next_piece() {
    std::shared_ptr<Tetromino> piece = q.front();
    q.pop();
    return piece;
}