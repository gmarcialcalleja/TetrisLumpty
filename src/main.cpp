#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"

int main()
{
	sf::RenderWindow window( sf::VideoMode( { 1500, 1600 } ), "SFML works!" );
	sf::RectangleShape shape( sf::Vector2f(38.f,38.f) );
	shape.setOutlineThickness(2.f);
	shape.setFillColor( sf::Color::Transparent );
	shape.setOutlineColor(sf::Color::White);
	Game game;
	sf::Clock clk;
	clk.restart();
	while ( window.isOpen())
	{
		sf::Time elapsed = clk.getElapsedTime();
		int32_t time = clk.getElapsedTime().asMicroseconds();
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() ) window.close();
			else if(const auto* key = event->getIf<sf::Event::KeyPressed>()) {
				if (key->code == sf::Keyboard::Key::Left)  game.move("left");
				if (key->code == sf::Keyboard::Key::Right) game.move("right");
				if (key->code == sf::Keyboard::Key::Up)    game.rotateClockwise();
				if (key->code == sf::Keyboard::Key::Down)  game.tick();
			}//
			
		}
		if(time > 715000) {
			game.tick();
			clk.restart();
		}
		window.clear(sf::Color::Black);
		game.renderBoard(window,shape);
		window.display();
	}
}
