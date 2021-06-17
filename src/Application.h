#pragma once

#include <memory>
#include "Board.h"

class Application
{
public:
	Application();

	void UpdateEvents();
	void Update();
	void Render();

	bool IsRunning() const;
	// User functions here

private:
	void LoadSettings();
	//


private:
	std::unique_ptr<sf::RenderWindow> window;
	sf::Event e;

	bool running = true;
	sf::Clock dtClock;

	int screenWidth;
	int screenHeight;

	// User variables here
	struct Settings
	{
		float cellSize;
		int boardWidth;
		int boardHeight;
		bool randomGenerated;
		float timeStep;
	};

	Settings settings;
	std::unique_ptr<Board> board;
	sf::Font font;
	sf::Text infoText;
	bool start = false;
	float timer = 0.0f;
	int generation = 0;
	//
};