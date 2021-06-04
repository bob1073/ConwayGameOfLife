#include "Application.h"
#include <cmath>

Application::Application()
    :
    window(sf::VideoMode(screenWidth, screenHeight), "Conway's Game of Life"),
    board(25, 25)
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

    if (!start)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            start = true;
        }
    }

    else
    {
        timer += dt;

        if (timer >= delay)
        {
            board.Update(dt);
            timer = 0.0f;
        }

    }
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
