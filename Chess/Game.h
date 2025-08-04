#pragma once
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

constexpr int SIZE{8};
constexpr int DESK_SIZE{ SIZE * SIZE };
constexpr int FIELD_SIZE{ 900 };
constexpr int CELL_SIZE{ 100 };
constexpr double MULT{100.f};

enum struct Cell
{
	Empty = 0,
	WPawn = 1,
	BPawn = 2,
	WKnight = 3,
	BKnight = 4,
	WBishop = 5,
	BBishop = 6,
	WRook = 7,
	BRook = 8,
	WQueen = 9,
	BQueen = 10,
	WKing = 11,
	BKing = 12
};

const std::vector<Cell> START_DESK = { Cell::BRook, Cell::BKnight, Cell::BBishop, Cell::BQueen, Cell::BKing, Cell::BBishop, Cell::BKnight, Cell::BRook,
										Cell::BPawn, Cell::BPawn, Cell::BPawn, Cell::BPawn, Cell::BPawn, Cell::BPawn, Cell::BPawn, Cell::BPawn,
										Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty,
										Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty,
										Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty,
										Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty, Cell::Empty,
										Cell::WPawn, Cell::WPawn, Cell::WPawn, Cell::WPawn, Cell::WPawn, Cell::WPawn, Cell::WPawn, Cell::WPawn,
										Cell::WRook, Cell::WKnight, Cell::WBishop, Cell::WQueen, Cell::WKing, Cell::WBishop, Cell::WKnight, Cell::WRook
};

const std::vector<std::string> PIECES = { "WFillPawn", "WFillRook", "WFillKnight", "WFillBishop", "WFillQueen", "WFillKing",
											"BFillPawn", "BFillRook", "BFillKnight", "BFillBishop", "BFillQueen", "BFillKing",
											"WHollowPawn", "WHollowRook", "WHollowKnight", "WHollowBishop", "WHollowQueen", "WHollowKing",
											"BHollowPawn", "BHollowRook", "BHollowKnight", "BHollowBishop", "BHollowQueen", "BHollowKing"
};

class Game : public sf::Drawable, public sf::Transformable
{
	std::vector<Cell> board;
	sf::Font font;
	std::map<std::string, sf::Texture> textures;
	sf::Vector2i touchPosition;

public:
	// === Инициализация игры ===
	Game();
	void Init();

	// === Рисование кадров ===
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawDesk(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawPieces(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawHighlight(sf::RenderTarget& target, sf::RenderStates states) const;

	// === Вспомогательные функции ===
	std::string wichTexture(int cell, bool pieceColor) const;
	Cell getCell(sf::Vector2i touchPosition) const;

	// === Обработка ввода ===
	void mouseLeftPressed(sf::Vector2i mousePosition);

	// === Действия в игре ===
	void move(int start_cell, int end_cell);
};