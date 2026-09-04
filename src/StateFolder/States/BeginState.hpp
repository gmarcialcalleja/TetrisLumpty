#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../../GameClass/Game.hpp"
#include <iostream>

class BeginState : public IGameState {
private:
    bool next_state;
public:
    BeginState() : next_state(false) {}
    void handleEvent(const sf::Event::KeyPressed* key){
        if (key->code == sf::Keyboard::Key::Enter) next_state = true;
    };
	void update(GameStateManager& manager) {
        if(next_state) {
            next_state = false;
            manager.TransitionState(1);
        }
    };
	void render(sf::RenderWindow& window){
        static sf::Font font;
        static bool fontLoaded = false;

        if (!fontLoaded) {
            fontLoaded = font.openFromFile("C:\\Windows\\Fonts\\arial.ttf");
        }
        if (!fontLoaded) return;

        // "Start Game" Text
        sf::Text startText(font, "Start Game", 250);
        startText.setFillColor(sf::Color::Cyan);
        startText.setPosition({100.f,100.f});
        window.draw(startText);
    }
};