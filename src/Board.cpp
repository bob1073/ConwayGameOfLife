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

int Board::Cell::CountAliveNeighbors(const std::vector<std::vector<Cell>>& cells, int boardWidth, int boardHeight) const
{
	const sf::Vector2f pos = cell.getPosition();
	const sf::Vector2i indexPos = sf::Vector2i(pos / size);
	int n = 0;

	for (int i = indexPos.x - 1; i <= indexPos.x + 1; ++i)
	{
		for (int j = indexPos.y - 1; j <= indexPos.y + 1; ++j)
		{
			if (i != indexPos.x || j != indexPos.y)
			{
				if (i >= 0 && i < boardWidth && j >= 0 && j < boardHeight)
				{
					if (cells[i][j].IsAlive())
					{
						n++;
					}
				}
			}
		}
	}

	return n;
}

void Board::Cell::Render(sf::RenderTarget& target)
{
	if (isAlive)
	{
		target.draw(cell);
	}
}

void Board::Cell::Update(const std::vector<std::vector<Cell>>& cells, int boardWidth, int boardHeight)
{
	const int numNeighbors = CountAliveNeighbors(cells, boardWidth, boardHeight);
	if (isAlive)
	{
		if (numNeighbors != 2 && numNeighbors != 3)
		{
			isAlive = false;
		}
	}
	else
	{
		if (numNeighbors == 3)
		{
			isAlive = true;
		}
	}
}

Board::Board(int width, int height)
	:
	cells(width, std::vector<Cell>(height, Cell())),
	width(width),
	height(height)
{
	const float cellSize = Cell::GetSize();

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			cells[i][j] = Cell(sf::Vector2f(i * cellSize , j * cellSize), (i + j) % 2);
		}
	}
}

void Board::Render(sf::RenderTarget& target)
{
	for (auto& cell : cells)
	{
		for (auto& cel : cell)
		{
			cel.Render(target);
		}
	}
}

void Board::Update(float dt)
{
	for (auto& cell : cells)
	{
		for (auto& cel : cell)
		{
			cel.Update(cells, width, height);
		}
	}
}
