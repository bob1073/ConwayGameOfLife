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

int Board::Cell::CountAliveNeighbors(const std::vector < std::vector<bool > >& lifeCells, int boardWidth, int boardHeight) const
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
					if (lifeCells[i][j] == true)
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

void Board::Cell::Update(const std::vector < std::vector<bool > >& lifeCells, int boardWidth, int boardHeight)
{
	const int numNeighbors = CountAliveNeighbors(lifeCells, boardWidth, boardHeight);
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
	lifeCells(width, std::vector<bool>(height, false)),
	width(width),
	height(height)
{
	const float cellSize = Cell::GetSize();

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			cells[i][j] = Cell(sf::Vector2f(i * cellSize , j * cellSize), false);
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

void Board::Update()
{
	CopyState();
	for (auto& cell : cells)
	{
		for (auto& cel : cell)
		{
			cel.Update(lifeCells, width, height);
		}
	}
}

void Board::UpdateInput(const sf::Vector2i& mousePos)
{
	const sf::FloatRect boardBounds = sf::FloatRect(0.0f, 0.0f, width * Cell::GetSize(), height * Cell::GetSize());
	const sf::Vector2i gridPos = sf::Vector2i(mousePos.x / Cell::GetSize(), mousePos.y / Cell::GetSize());

	if (boardBounds.contains(static_cast<sf::Vector2f>(mousePos)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			cells[gridPos.x][gridPos.y].Revive();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			cells[gridPos.x][gridPos.y].Kill();
		}
	}
	
}

void Board::CopyState()
{
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			lifeCells[i][j] = cells[i][j].IsAlive();
		}
	}
}
