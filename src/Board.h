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
	void Update(float dt);

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
		int CountAliveNeighbors(const std::vector<Cell>& cells) const;
		void Render(sf::RenderTarget& target);
		void Update(float dt);

		// Getters
		bool IsAlive() const { return isAlive; }
		static float GetSize() { return size; }

	private:
		sf::RectangleShape cell;
		bool isAlive = false;

		static constexpr float size = 20.0f;
	};

private:
	std::vector<Cell> cells;
	int width;
	int height;
};

