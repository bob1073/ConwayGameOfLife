#include "Board.h"
#include <random>

Board::Cell::Cell(const sf::Vector2f& pos, float size, bool isAlive)
	:
	m_size{ size },
	m_isAlive{ isAlive }
{
	m_cell.setPosition(pos);
	m_cell.setSize({ size, size });
	m_cell.setOutlineThickness(-1.0f);
	m_cell.setFillColor(sf::Color::White);
	m_cell.setOutlineColor(sf::Color::Black);
}

void Board::Cell::revive()
{
	m_isAlive = true;
}

void Board::Cell::kill()
{
	m_isAlive = false;
}

int Board::Cell::countAliveNeighbors(const Board& board) const
{
	const sf::Vector2f pos = m_cell.getPosition();
	const sf::Vector2i indexPos = static_cast<sf::Vector2i>(
		(pos - board.getPosition()) / m_size
	);
	const int boardWidth = board.getWidth();
	const int boardHeight = board.getHeight();
	int n = 0;

	for (int i = indexPos.x - 1; i <= indexPos.x + 1; ++i)
	{
		for (int j = indexPos.y - 1; j <= indexPos.y + 1; ++j)
		{
			if (i != indexPos.x || j != indexPos.y)
			{
				if (i >= 0 && i < boardWidth && j >= 0 && j < boardHeight)
				{
					if (board.m_liveCells[i][j] == true)
					{
						n++;
					}
				}
			}
		}
	}

	return n;
}

void Board::Cell::render(sf::RenderTarget& target)
{
	if (m_isAlive)
	{
		target.draw(m_cell);
	}
}

void Board::Cell::update(const Board& board)
{
	const int numNeighbors = countAliveNeighbors(board);
	if (m_isAlive)
	{
		if (numNeighbors != 2 && numNeighbors != 3)
		{
			kill();
		}
	}
	else
	{
		if (numNeighbors == 3)
		{
			revive();
		}
	}
}

Board::Board(const sf::Vector2f& pos, 
	float cellSize, int width, int height, bool randomGenerated)
	:
	m_pos{ pos },
	m_cellSize{ cellSize },
	m_width{ width },
	m_height{ height },
	m_cells{ width, std::vector<Cell>(height, Cell()) },
	m_liveCells{ width, std::vector<bool>(height, false) }
{

	m_border.setPosition(pos);
	m_border.setSize(sf::Vector2f(cellSize * width, cellSize * height));
	m_border.setFillColor(sf::Color::Transparent);
	m_border.setOutlineThickness(s_borderSize);
	m_border.setOutlineColor(sf::Color(120, 120, 120));

	if (randomGenerated)
	{
		std::random_device rd;
		std::mt19937 random(rd());
		std::uniform_int_distribution<int> randomizer(0, 1);

		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				const int val = randomizer(random);
				m_cells[i][j] = Cell(
					{ pos.x + i * cellSize, pos.y + j * cellSize }, cellSize, val
				);
			}
		}
	}
	else
	{
		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				m_cells[i][j] = Cell(
					{ pos.x + i * cellSize, pos.y + j * cellSize }, cellSize, false
				);
			}
		}
	}
	
}

void Board::render(sf::RenderTarget& target)
{
	target.draw(m_border);

	for (auto& cell : m_cells)
	{
		for (auto& cel : cell)
		{
			cel.render(target);
		}
	}
}

void Board::update()
{
	copyState();
	for (auto& cell : m_cells)
	{
		for (auto& cel : cell)
		{
			cel.update(*this);
		}
	}
}

void Board::updateInput(const sf::Vector2i& mousePos)
{
	const sf::FloatRect boardBounds = sf::FloatRect(
		25.0f, 25.0f,  m_width * m_cellSize, m_height * m_cellSize
	);
	const sf::Vector2i gridPos = sf::Vector2i(
		static_cast<int>((mousePos.x - m_pos.x)/ m_cellSize), 
		static_cast<int>((mousePos.y - m_pos.y) / m_cellSize)
	);

	if (boardBounds.contains(static_cast<sf::Vector2f>(mousePos)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_cells[gridPos.x][gridPos.y].revive();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			m_cells[gridPos.x][gridPos.y].kill();
		}
	}
	
}

int Board::countAliveCells() const
{
	int n = 0;
	for (auto lCells : m_liveCells)
	{
		for (auto lc : lCells)
		{
			if (lc)
			{
				n++;
			}
		}
	}
	return n;
}

void Board::copyState()
{
	for (int i = 0; i < m_width; ++i)
	{
		for (int j = 0; j < m_height; ++j)
		{
			m_liveCells[i][j] = m_cells[i][j].isAlive();
		}
	}
}
