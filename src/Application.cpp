#include "Application.h"
#include <cmath>

Application::Application()
    :
    window(sf::VideoMode(screenWidth, screenHeight), "Conway's Game of Life"),
    board(50, 50)
{
    
}

Application::~Application()
{
}

void Application::UpdateEvents()
{
    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            running = false;
    }
}

void Application::Update()
{
    const float dt = dtClock.restart().asSeconds();


       
}

void Application::Render()
{
    window.clear();
    // Render things here
    board.Render(window);
    //
    window.display();
}

bool Application::IsRunning() const
{
    return running;
}
