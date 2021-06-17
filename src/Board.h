#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
public:
	// Constructors
	Board() = default;
	
	Board(const sf::Vector2f& pos, float cellSize, int width, int height, bool randomGenerated);

	// Functions
	void Render(sf::RenderTarget& target);
	void Update();
	void UpdateInput(const sf::Vector2i& mousePos);

	// Getters
	const std::vector < std::vector < bool > >& GetLifeCells() const { return lifeCells; }
	const sf::Vector2f GetPosition() const { return pos; }
	const int GetWidth() const { return width; }
	const int GetHeight() const { return width; }

private:
	// Functions
	void CopyState();

private:
	class Cell
	{
	public:
		// Constructors
		Cell() = default;
		Cell(const sf::Vector2f& pos, float size, bool isAlive);

		// Functions
		void Revive();
		void Kill();
		int CountAliveNeighbors(const Board& board) const;
		void Render(sf::RenderTarget& target);
		void Update(const Board& board);

		// Getters
		bool IsAlive() const { return isAlive; }

	private:
		sf::RectangleShape cell;
		bool isAlive = false;

		float size;
	};

private:
	// Border
	sf::RectangleShape border;

	// Board
	std::vector < std::vector< Cell> > cells;
	sf::Vector2f pos;
	float cellSize;
	int width;
	int height;

	// Logic
	std::vector < std::vector<bool > > lifeCells;

	// Constants
	static constexpr float borderSize = 2.0f;
};

