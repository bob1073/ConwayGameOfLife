#include "Application.h"
#include <fstream>
#include <iostream>

Application::Application()
    :
    e(),
    settings()
{
    // Load settings
    LoadSettings();

    // Load font
    if (!font.loadFromFile("Fonts/Roboto-Light.ttf"))
    {
        sf::err() << "Failed to load font";
    }

    // Create board
    board = std::make_unique<Board>(sf::Vector2f(25.0f, 25.0f), settings.cellSize, settings.boardWidth, settings.boardHeight, settings.randomGenerated);

    // Create window
    const float offsetX = settings.cellSize * settings.boardWidth + 50.0f;
    screenWidth = int(offsetX + 200.0f);
    screenHeight = int(settings.cellSize * settings.boardHeight + 50.0f);
    window = std::make_unique< sf::RenderWindow>(sf::VideoMode(screenWidth, screenHeight), "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close);

    // Simple UI
    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(offsetX + 10.0f, 50.0f);
    infoText.setString("Generation: 0\n\nPopulation: 0");
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
            ++generation;
            timer = 0.0f;
        }

        infoText.setString("Generation: " + std::to_string(generation) + "\n\nPopulation: " + std::to_string(board->CountAliveCells()));
    }
}

void Application::Render()
{
    window->clear();
    // Render things here
    board->Render(*window);
    window->draw(infoText);
    //
    window->display();
}

bool Application::IsRunning() const
{
    return running;
}

void Application::LoadSettings()
{
    std::ifstream in("Config/settings.ini");

    if (!in)
    {
        sf::err() << "Failed to load settings.ini";
    }
    else
    {
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
    }
}
