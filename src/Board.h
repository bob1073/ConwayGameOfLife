#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
public:
	// Constructor
	Board(int width, int height);

	// Functions
	void Render(sf::RenderTarget& target);
	void Update();
	void UpdateInput(const sf::Vector2i& mousePos);

private:
	class Cell
	{
	public:
		// Constructor
		Cell() = default;
		Cell(const sf::Vector2f& pos, bool isAlive);

		// Functions
		void Revive();
		void Kill();
		int CountAliveNeighbors(const std::vector < std::vector<bool > >& lifeCells, int boardWidth, int boardHeight) const;
		void Render(sf::RenderTarget& target);
		void Update(const std::vector < std::vector<bool > >& lifeCells, int boardWidth, int boardHeight);

		// Getters
		bool IsAlive() const { return isAlive; }
		static float GetSize() { return size; }

	private:
		sf::RectangleShape cell;
		bool isAlive = false;

		static constexpr float size = 20.0f;
	};

private:
	std::vector < std::vector< Cell> > cells;
	std::vector < std::vector<bool > > lifeCells;
	int width;
	int height;

	// Private functions
	void CopyState();
};

