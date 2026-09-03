#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"

class GameStateManager;

class IGameState {
public:
	virtual ~IGameState() = default;
	virtual void handleEvent(const sf::Event::KeyPressed* key) = 0;
	virtual void update(GameStateManager& manager) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};


class GameStateManager{
private:
	std::vector<std::unique_ptr<IGameState>> states;// use enums ig
	int state_idx;
	sf::Clock clk;
public:
	GameStateManager(std::vector<std::unique_ptr<IGameState>> states_) : states(std::move(states_)), state_idx(0) {}
	void TransitionState(int new_state_idx) {state_idx = new_state_idx;}
	void handleEvent(const sf::Event::KeyPressed* key) {states.at(state_idx)->handleEvent(key);}
	void update() {states.at(state_idx)->update(*this);}
	void render(sf::RenderWindow& window) {states.at(state_idx)->render(window);}
	int32_t getTime() {return clk.getElapsedTime().asMicroseconds();}
	void restartClock() {clk.restart();}
};

class PlayingGameState : public IGameState {
public:
	Game game;
	PlayingGameState(){}
	void handleEvent(const sf::Event::KeyPressed* key) {
		if (key->code == sf::Keyboard::Key::Left)  game.move("left");
		if (key->code == sf::Keyboard::Key::Right) game.move("right");
		if (key->code == sf::Keyboard::Key::Up)    game.rotateClockwise();
		if (key->code == sf::Keyboard::Key::Down)  game.tick();
		if (key->code == sf::Keyboard::Key::LShift)  game.hold();
		if (key->code == sf::Keyboard::Key::Space)  game.drop();
	}
	void update(GameStateManager& manager) override  {
		if(manager.getTime() > game.getTickSpeed()) {
			game.tick();
			manager.restartClock();
		}
		if(game.isOver()) {
            manager.TransitionState(0);
        }
	}

	void render(sf::RenderWindow& window) {
		game.renderBoard(window);
		game.renderHold(window);
	}
};



