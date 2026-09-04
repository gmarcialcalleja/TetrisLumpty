#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include "IGameState.hpp"
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
	void render(sf::RenderWindow& window) {
		states.at(state_idx)->render(window);
	}
	int32_t getTime() {return clk.getElapsedTime().asMicroseconds();}
	void restartClock() {clk.restart();}
	
};