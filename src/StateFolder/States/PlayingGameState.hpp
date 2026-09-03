#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../../GameClass/Game.hpp"

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
            manager.TransitionState(1);
        }
	}

	void render(sf::RenderWindow& window) {
		game.renderBoard(window);
		game.renderHold(window);
	}
};



