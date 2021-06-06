#include "Application.h"
#include <fstream>

Application::Application()
    :
    e(),
    settings()
{
    // Load settings
    std::ifstream in("Config/settings.ini");

    for (std::string s; std::getline(in, s); )
    {
        if (s == "# Cell size")
        {
            in >> settings.cellSize;
        }
        if (s == "# Board width")
        {
            in >> settings.boardWidth;
        }
        if (s == "# Board height")
        {
            in >> settings.boardHeight;
        }
        if (s == "# Initial patron random (1 yes, 0 not)")
        {
            in >> settings.randomGenerated;
        }
        if (s == "# Time step")
        {
            in >> settings.timeStep;
        }
    }

    screenWidth = int(settings.cellSize * settings.boardWidth);
    screenHeight = int(settings.cellSize * settings.boardHeight);

    // Create window
    window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight), "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close);

    // Create board
    board = new Board(settings.cellSize, settings.boardWidth, settings.boardHeight, settings.randomGenerated);
}

Application::~Application()
{
    delete board;
    board = nullptr;

    delete window;
    window = nullptr;
}

void Application::UpdateEvents()
{
    while (window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            running = false;
    }
}

void Application::Update()
{
    const float dt = dtClock.restart().asSeconds();
    const sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        start = true;
    }

    if (!start)
    {
        if (!settings.randomGenerated)
        {
            board->UpdateInput(mousePos);
        }
    }
    else
    {
        timer += dt;

        if (timer >= settings.timeStep)
        {
            board->Update();
            timer = 0.0f;
        }
    }
}

void Application::Render()
{
    window->clear();
    // Render things here
    board->Render(*window);
    //
    window->display();
}

bool Application::IsRunning() const
{
    return running;
}
