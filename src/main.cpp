
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "./StateFolder/GameStateManager.hpp"
#include "./StateFolder/States/PlayingGameState.hpp"
#include "./StateFolder/States/GameOverState.hpp"




int main()
{
	sf::RenderWindow window( sf::VideoMode( { 1500, 1600 } ), "SFML works!" );
	std::unique_ptr<GameOverState> end = std::make_unique<GameOverState>();
	std::unique_ptr<PlayingGameState> play = std::make_unique<PlayingGameState>();
	std::vector<std::unique_ptr<IGameState>> states;
	states.push_back(std::move(play));
	states.push_back(std::move(end));
	GameStateManager manager(std::move(states));
	
	while ( window.isOpen())
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() ) window.close();
			else if(const auto* key = event->getIf<sf::Event::KeyPressed>()) {
				manager.handleEvent(key);
			}
			
		}
		manager.update();
		window.clear(sf::Color::Black);
		manager.render(window);
		window.display();
	}
}
