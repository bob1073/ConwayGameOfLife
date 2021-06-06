#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
public:
	// Constructors
	Board() = default;
	Board(float cellSize, int width, int height, bool randomGenerated);

	// Functions
	void Render(sf::RenderTarget& target);
	void Update();
	void UpdateInput(const sf::Vector2i& mousePos);

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
		int CountAliveNeighbors(const std::vector < std::vector<bool > >& lifeCells, int boardWidth, int boardHeight) const;
		void Render(sf::RenderTarget& target);
		void Update(const std::vector < std::vector<bool > >& lifeCells, int boardWidth, int boardHeight);

		// Getters
		bool IsAlive() const { return isAlive; }

	private:
		sf::RectangleShape cell;
		bool isAlive = false;

		float size;
	};

private:
	std::vector < std::vector< Cell> > cells;
	std::vector < std::vector<bool > > lifeCells;
	float cellSize;
	int width;
	int height;

	// Private functions
	void CopyState();
};

