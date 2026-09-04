#pragma once
#include <vector>
#include <array>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ShapeDatabase.hpp"
#include "Board.hpp"
#include "./Observer/ScoreTracker.hpp"
#include "Tetromino.hpp"
#include "Factory.hpp"


class Game {
private:
    Board board;
    TetrisFactory factory;
    std::shared_ptr<Tetromino> piece;
    bool alreadyHeld;
    int level;
    sf::RectangleShape shape;
    bool gameOver;
    ScoreTracker score;
    std::vector<sf::Color> colors{
        sf::Color::Transparent, sf::Color::Red, sf::Color::Yellow, sf::Color::Cyan,
        sf::Color::White, sf::Color::Blue, sf::Color::Magenta, sf::Color::Green
    };//
    const std::array<int32_t, 30> levels_array{ 
        798684, 715488, 632292, 549096, 465899, 382703, 299507, 216310, 
        133114, 99836, 83196, 83196, 83196, 66557, 66557, 66557, 49918, 49918, 49918, 
        33279, 33279, 33279, 33279, 33279, 33279, 33279, 33279, 33279, 33279, 16639    
    };
public:
    Game() : factory(), piece(factory.load_next_piece()), alreadyHeld(false), level(0), gameOver(false), shape(sf::Vector2f(38.f,38.f)){
        board.attach_observer(&score);
        shape.setOutlineThickness(2.f);
        shape.setFillColor( sf::Color::Transparent );
        shape.setOutlineColor(sf::Color::White);
    }
    const std::array<std::pair<int, int>, 4>& getPieceMatrix();
    void tick();
    int32_t getTickSpeed() {return levels_array.at(level);}
    void printBoard();
    void renderBoard(sf::RenderWindow& window);
    void move(std::string move);
    void rotateClockwise();
    void hold();
    bool isOver() {return gameOver;}
    void drop();
    void resetBoard() {board.reset();}
    void renderHold(sf::RenderWindow& window) ;
    void setOver(bool var) {gameOver = var;}
    // add member variables of Concrete Observors
    // add a getscore ig to call in main and render
};
//--------------------------------------------------------------------------------------------------


void Game::renderBoard(sf::RenderWindow& window) {
    shape.setOutlineThickness(2.f);
    auto Board_copy = board.getBoardCopy();
    auto TetrisMatrix = getPieceMatrix();
    float x_offset = 400;
    float y_offset = 200;
    for(const auto& [y, x]: TetrisMatrix) 
        Board_copy.at(y + piece->getPosition().first).at(x+piece->getPosition().second) = piece->getType();
    
    for(float y = 0; y < board.num_rows(); y++) {
        for(float x = 0; x < board.num_cols(); x++) {
            shape.setFillColor(colors.at(static_cast<int>(Board_copy.at(y).at(x))));
            shape.setPosition({x*40 + x_offset, y*40 + y_offset});
            window.draw(shape);
        }
    }
}

void Game::renderHold(sf::RenderWindow& window) {
    std::vector<std::vector<ShapeType>> mini_matrix = std::vector(4, std::vector<ShapeType>(4, ShapeType::Empty));
    if(factory.show_held_piece() == nullptr) return;
    Tetromino held_piece(static_cast<int>(factory.show_held_piece()->getType()));
    auto TetrisMatrix = ShapeDatabase::getMatrix(held_piece.getType(), held_piece.getRotation());
    float x_offset = 50;
    float y_offset = 200;
    for(const auto& [y, x]: TetrisMatrix) 
        mini_matrix.at(y).at(x) = held_piece.getType();
    
    for(float y = 0; y < 4; y++) {
        for(float x = 0; x < 4; x++) {
            shape.setFillColor(colors.at(static_cast<int>(mini_matrix.at(y).at(x))));
            shape.setPosition({x*40 + x_offset, y*40 + y_offset});
            shape.setOutlineThickness(0.f);
            window.draw(shape);
        }
    }
}

const std::array<std::pair<int, int>, 4>& Game::getPieceMatrix() {
    return ShapeDatabase::getMatrix(piece->getType(), piece->getRotation());
}
//save the current piece
//set piece to held piece
//if theres no held piece we js load_next_piece
//if we already held a piece we cant hold again in the same turn
void Game::hold() {
    if(alreadyHeld) return;
    piece->default_state();
    factory.hold(piece);
    piece = factory.load_next_piece();
    alreadyHeld = true;
}

void Game::drop() {
    while(board.isDropValid(piece))
        piece->down(); // execute
    board.lock(piece);
    board.clear_if_fill(piece->getPosition().first, getPieceMatrix());

    // if there is a line clear then in the board array, we want to like
    // clear the vector where the line is, then js move everything down 1
    piece->default_state();
    if(factory.isEmpty()) factory.fill_stack();
    piece = factory.load_next_piece();
    alreadyHeld = false;
    
}
void Game::tick() {
    //calculate next state Matrix
    if(board.isDropValid(piece)) {
        piece->down(); // execute
    } else {
        if(piece->getPosition().first == 0) {
            setOver(true);
            return;
        }
        board.lock(piece);
        board.clear_if_fill(piece->getPosition().first, getPieceMatrix());

        piece->default_state();
        if(factory.isEmpty()) factory.fill_stack();
        piece = factory.load_next_piece();
        alreadyHeld = false;
    }
}

void Game::printBoard() {
    auto Board_copy = board.getBoardCopy();
    std::cout << Board_copy.at(0).size() << std::endl;
}

void Game::move(std::string move) {
    if(board.isMoveValid(piece, move)) {
        piece->move(move);
    }
}
void Game::rotateClockwise() {
    // define a bunch of predefined positions
    // get the right position vector based off rotation, I's a special case ig
    // pass in the rotation and the piece
    if(board.isCWValid(piece)) {
        piece->rotateClockwise();
        return;
    }
    const auto& positions = ShapeDatabase::getKick(piece->getType(), piece->getRotation());

    for(const auto& position: positions) {
        std::pair<int,int> pos = {position.first + piece->getPosition().first, position.second + piece->getPosition().second};
        if(board.isCWValid(piece,pos)) {
            piece->setPosition(pos);
            piece->rotateClockwise();
            break;
        }
    // if board.isCWValid(piece, position) piece.setPosition(position), piece->rotateCW();
    }
}