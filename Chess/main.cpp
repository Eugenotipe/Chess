#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::Vector2i touchPosition(0, 0);

	sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "Chess");
	window.setFramerateLimit(60);
	sf::Image icon;
	icon.loadFromFile("img/WQueen.png");
	window.setIcon(sf::Vector2u(32, 32), icon.getPixelsPtr());

	Game game;
	game.setPosition({50.f, 50.f});

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				{
					window.close();
				}
			}
			if (const auto* mouseKeyPressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mouseKeyPressed->button == sf::Mouse::Button::Left)
				{
					game.mouseLeftPressed(mouseKeyPressed->position);
				}
			}
		}

		window.clear();
		window.draw(game);
		window.display();
	}

	return 0;
}