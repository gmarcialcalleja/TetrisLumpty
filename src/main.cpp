
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "StateStuff.hpp"
#include "Game.hpp"


//2 states
// Playing Game State and a End Game State
// Game class has all the playing game state logic
// have a game state manager to switch between states

//Game State Manager
// hold the window, the keys, and the current state
// method TransitionState
// update
// render 
// when gamestate manager calls update, it'd call currentstate->update,
// when gamestate manager calls render itd call currentstate->render





int main()
{
	sf::RenderWindow window( sf::VideoMode( { 1500, 1600 } ), "SFML works!" );
	std::unique_ptr<PlayingGameState> play = std::make_unique<PlayingGameState>();
	std::vector<std::unique_ptr<IGameState>> states;
	states.push_back(std::move(play));
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
