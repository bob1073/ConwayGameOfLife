#pragma once

#include <memory>
#include "Board.h"

class Application
{
public:
	struct Settings
	{
		float cellSize;
		int boardWidth;
		int boardHeight;
		bool randomGenerated;
		float timeStep;
	};

public:
	Application();

	void updateEvents();
	void update();
	void render();

	bool isRunning() const { return m_running; }

private:
	void loadSettings();


private:
	std::unique_ptr<sf::RenderWindow> m_window{};
	std::unique_ptr<Board> m_board{};
	sf::Event m_event{};
	sf::Clock m_dtClock{};

	bool m_running{ true };
	bool m_start{ false };
	float m_timer{ 0.0f };
	int m_generation{ 0 };

	int m_screenWidth{};
	int m_screenHeight{};

	Settings m_settings{};
	
	sf::Font m_font{};
	sf::Text m_infoText{};
	
	
};