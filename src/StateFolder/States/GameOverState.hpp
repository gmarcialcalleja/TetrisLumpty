#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../../GameClass/Game.hpp"

class GameOverState : public IGameState {
public: 
    GameOverState() {}
    void handleEvent(const sf::Event::KeyPressed* key) override {
        // put begin event logic here;
    }
	void update(GameStateManager& manager) override {
        //manager . transition state ig;
    }
	void render(sf::RenderWindow& window) override {}
};