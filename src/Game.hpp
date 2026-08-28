#include <vector>
#include <array>
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ShapeDatabase.hpp"
#include "Board.hpp"
#include "Tetromino.hpp"
#include "Factory.hpp"


class Game {
private:
    Board board;
    TetrisFactory factory;
    std::shared_ptr<Tetromino> piece;
    std::vector<sf::Color> colors{
        sf::Color::Transparent, sf::Color::Red, sf::Color::Yellow, sf::Color::Cyan,
        sf::Color::White, sf::Color::Blue, sf::Color::Magenta, sf::Color::Green
    };
public:
    Game() : factory(), piece(factory.load_next_piece()) {}
    const std::array<std::pair<int, int>, 4>& getPieceMatrix();
    void tick();
    void printBoard();
    void renderBoard(sf::RenderWindow& window, sf::RectangleShape& shape);
    void move(std::string move);
    void rotateClockwise();
};
//--------------------------------------------------------------------------------------------------
void Game::renderBoard(sf::RenderWindow& window, sf::RectangleShape& shape) {
    
    auto Board_copy = board.getBoardCopy();
    auto TetrisMatrix = getPieceMatrix();
    float x_offset = 200;
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
const std::array<std::pair<int, int>, 4>& Game::getPieceMatrix() {
    return ShapeDatabase::getMatrix(piece->getType(), piece->getRotation());
}
void Game::tick() {
    //calculate next state Matrix
    auto TetrisMatrix = getPieceMatrix();
    if(board.isDropValid(TetrisMatrix, piece->getPosition())) {
        piece->down(); // execute
    } else {
        board.lock(piece);
        board.clear_if_fill(piece->getPosition().first, TetrisMatrix);

        // if there is a line clear then in the board array, we want to like
        // clear the vector where the line is, then js move everything down 1
        piece->default_state();
        if(factory.isEmpty()) factory.fill_queue();
        piece = factory.load_next_piece();
    }
}
void Game::printBoard() {
    auto Board_copy = board.getBoardCopy();
    std::cout << Board_copy.at(0).size() << std::endl;
}

void Game::move(std::string move) {
    auto TetrisMatrix = getPieceMatrix();
    if(board.isMoveValid(TetrisMatrix, piece->getPosition(), move)) {
        piece->move(move);
    }
}
void Game::rotateClockwise() {
    auto TetrisMatrix = ShapeDatabase::getMatrix(piece->getType(), (piece->getRotation()+1)%4);
    if(board.isCWValid(TetrisMatrix, piece->getPosition())) 
        piece->rotateClockwise();
}