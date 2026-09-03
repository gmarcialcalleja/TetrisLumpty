#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class GameStateManager;

class IGameState {
public:
	virtual ~IGameState() = default;
	virtual void handleEvent(const sf::Event::KeyPressed* key) = 0;
	virtual void update(GameStateManager& manager, int32_t time) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};
