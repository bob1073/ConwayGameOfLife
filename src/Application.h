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
	sf::RenderWindow window;
	sf::Event e;

	bool running = true;
	sf::Clock dtClock;

	static constexpr int screenWidth = 800;
	static constexpr int screenHeight = 600;

	// User variables here
	Board board;
	bool start = false;
	float timer = 0.0f;
	static constexpr float delay = 0.5f;
	//
};