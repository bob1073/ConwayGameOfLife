#pragma once

#include "Board.h"

class Application
{
public:
	Application();
	~Application();

	void UpdateEvents();
	void Update();
	void Render();

	bool IsRunning() const;
	// User functions here

	//
private:
	sf::RenderWindow* window;
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
	Board* board;
	bool start = false;
	float timer = 0.0f;
	static constexpr float delay = 0.1f;
	//
};