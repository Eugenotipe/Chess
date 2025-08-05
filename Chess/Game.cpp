#include "Game.h"

Game::Game()
{
	font.openFromFile("fonts/alagard-12px-unicode.ttf");
	for (std::string piece : PIECES)
	{
		textures[piece] = sf::Texture();
		textures[piece].loadFromFile("img/" + piece + ".png");
	}
	Init();
}

void Game::Init()
{
	board = START_DESK;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawDesk(target, states);
	drawHighlight(target, states);
	drawPieces(target, states);
	

}

void Game::drawDesk(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
	shape.setFillColor(sf::Color(101, 67, 33));
	target.draw(shape, states);

	for (unsigned int i{ 0 }; i < DESK_SIZE; i++)
	{
		sf::Vector2f position(i % SIZE * MULT + 50.f, i / SIZE * MULT + 50.f);
		sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		shape.setPosition(position);
		if (i / SIZE % 2 == 0)
		{
			shape.setFillColor((i % 2 == 0) ? sf::Color(245, 245, 220, 255) : sf::Color(50, 50, 50, 255));
		}
		else
		{
			shape.setFillColor((i % 2 == 0) ? sf::Color(50, 50, 50, 255) : sf::Color(245, 245, 220, 255));
		}
		target.draw(shape, states);
	}

	sf::Text text(font, "", 30);

	for (unsigned short int i{ 0 }; i < SIZE; i++)
	{
		sf::Vector2f position(i % SIZE * MULT + 80.f, 9.f);
		char sign{ 'A' };
		text.setString(char(sign + i));
		text.setPosition(position);
		text.setFillColor(sf::Color(212, 175, 55, 255));
		target.draw(text, states);
		position.y = 856.f;
		text.setPosition(position);
		target.draw(text, states);
	}

	for (unsigned short int i{ 0 }; i < SIZE; i++)
	{
		sf::Vector2f position(20.f, i % SIZE * MULT + 80.f);
		char sign{ '1' };
		text.setString(char(sign + i));
		text.setPosition(position);
		text.setFillColor(sf::Color(212, 175, 55, 255));
		target.draw(text, states);
		position.x = 870.f;
		text.setPosition(position);
		target.draw(text, states);
	}
}

void Game::drawPieces(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (unsigned int i{ 0 }; i < DESK_SIZE; i++)
	{
		if (board[i] != Cell::Empty)
		{
			sf::Vector2f position(i % SIZE * MULT + 50.f, i / SIZE * MULT + 50.f);
			sf::RectangleShape shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			shape.setPosition(position);
			switch (board[i])
			{
			case Cell::BPawn:
			{
				shape.setTexture(&textures.at("BPawn"));
				break;
			}
			case Cell::BRook:
			{
				shape.setTexture(&textures.at("BRook"));
				break;
			}
			case Cell::BKnight:
			{
				shape.setTexture(&textures.at("BKnight"));
				break;
			}
			case Cell::BBishop:
			{
				shape.setTexture(&textures.at("BBishop"));
				break;
			}
			case Cell::BQueen:
			{
				shape.setTexture(&textures.at("BQueen"));
				break;
			}
			case Cell::BKing:
			{
				shape.setTexture(&textures.at("BKing"));
				break;
			}
			case Cell::WPawn:
			{
				shape.setTexture(&textures.at("WPawn"));
				break;
			}
			case Cell::WRook:
			{
				shape.setTexture(&textures.at("WRook"));
				break;
			}
			case Cell::WKnight:
			{
				shape.setTexture(&textures.at("WKnight"));
				break;
			}
			case Cell::WBishop:
			{
				shape.setTexture(&textures.at("WBishop"));
				break;
			}
			case Cell::WQueen:
			{
				shape.setTexture(&textures.at("WQueen"));
				break;
			}
			case Cell::WKing:
			{
				shape.setTexture(&textures.at("WKing"));
				break;
			}
			}
			target.draw(shape, states);
		}
	}
}

void Game::drawHighlight(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (touchPosition != sf::Vector2i(0, 0) && getCell(touchPosition) != Cell::Empty)
	{
		sf::RectangleShape highlightShape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		highlightShape.setFillColor(sf::Color(100, 200, 220, 150));
		highlightShape.setPosition(sf::Vector2f((touchPosition.x - 1) * 100 + 50, (touchPosition.y - 1) * 100 + 50));
		target.draw(highlightShape, states);
	}
}

void Game::mouseLeftPressed(sf::Vector2i mousePosition)
{
	if ((mousePosition.x >= 100 && mousePosition.x <= 900) && (mousePosition.y >= 100 && mousePosition.y <= 900))
	{
		touchPosition = sf::Vector2i(mousePosition.x / 100, mousePosition.y / 100);
	}
	else
	{
		touchPosition = sf::Vector2i(0, 0);
	}
}

Cell Game::getCell(sf::Vector2i touchPosition) const
{
	return board[(touchPosition.y - 1) * SIZE + (touchPosition.x - 1)];
}