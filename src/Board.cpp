#include "Board.h"

Board::Cell::Cell(const sf::Vector2f& pos, bool isAlive)
	:
	isAlive(isAlive)
{
	cell.setPosition(pos);
	cell.setSize({ size, size });
	cell.setOutlineThickness(-1.0f);
	cell.setFillColor(sf::Color::White);
	cell.setOutlineColor(sf::Color::Black);
}

void Board::Cell::Revive()
{
	isAlive = true;
}

void Board::Cell::Kill()
{
	isAlive = false;
}

int Board::Cell::CountAliveNeighbors(const std::vector<Cell>& cells) const
{
	const sf::Vector2f pos = cell.getPosition();

	
	return 0;
}

void Board::Cell::Render(sf::RenderTarget& target)
{
	if (isAlive)
	{
		target.draw(cell);
	}
}

void Board::Cell::Update(float dt)
{
	
}

Board::Board(int width, int height)
	:
	cells(width*height),
	width(width),
	height(height)
{
	const float cellSize = Cell::GetSize();

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			cells.emplace_back(sf::Vector2f(i * cellSize , j * cellSize), false);
		}
	}
}

void Board::Render(sf::RenderTarget& target)
{
	for (auto& cell : cells)
	{
		cell.Render(target);
	}
}

void Board::Update(float dt)
{
}
