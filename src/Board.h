#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
public:
	// Constructors
	Board() = default;
	
	Board(const sf::Vector2f& pos, 
		float cellSize, int width, int height, bool randomGenerated);

	// Functions
	void render(sf::RenderTarget& target);
	void update();
	void updateInput(const sf::Vector2i& mousePos);
	int countAliveCells() const;

	// Getters
	const std::vector < std::vector < bool > >& getLifeCells() const { return m_liveCells; }
	const sf::Vector2f getPosition() const { return m_pos; }
	const int getWidth() const { return m_width; }
	const int getHeight() const { return m_width; }

private:
	void copyState();

private:
	class Cell
	{
	public:
		// Constructors
		Cell() = default;
		Cell(const sf::Vector2f& pos, float size, bool isAlive);

		// Functions
		void revive();
		void kill();
		int countAliveNeighbors(const Board& board) const;
		void render(sf::RenderTarget& target);
		void update(const Board& board);

		// Getters
		bool isAlive() const { return m_isAlive; }

	private:
		sf::RectangleShape m_cell{};
		bool m_isAlive{ false };

		float m_size{};
	};

private:
	// Border
	sf::RectangleShape m_border{};

	// Board
	std::vector < std::vector< Cell> > m_cells{};
	sf::Vector2f m_pos{};
	float m_cellSize{};
	int m_width{};
	int m_height{};

	// Logic
	std::vector < std::vector<bool > > m_liveCells{};

	// Constants
	static constexpr float s_borderSize{ 2.0f };
};

