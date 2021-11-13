#include "Application.h"
#include <fstream>
#include <iostream>

Application::Application()
{
    // Load settings
    loadSettings();

    // Load font
    if (!m_font.loadFromFile("Fonts/Roboto-Light.ttf"))
    {
        sf::err() << "Failed to load font";
    }
                                                                               
    // Create board
    m_board = std::make_unique<Board>(
        sf::Vector2f(25.0f, 25.0f), 
        m_settings.cellSize, m_settings.boardWidth, m_settings.boardHeight, 
        m_settings.randomGenerated
    );

    // Create window
    const float offsetX = m_settings.cellSize * m_settings.boardWidth + 50.0f;
    m_screenWidth = int(offsetX + 200.0f);
    m_screenHeight = int(m_settings.cellSize * m_settings.boardHeight + 50.0f);
    m_window = std::make_unique< sf::RenderWindow>(
        sf::VideoMode(m_screenWidth, m_screenHeight), 
        "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close
    );

    // Simple UI
    m_infoText.setFont(m_font);
    m_infoText.setCharacterSize(20);
    m_infoText.setFillColor(sf::Color::White);
    m_infoText.setPosition(offsetX + 10.0f, 50.0f);
    m_infoText.setString("Generation: 0\n\nPopulation: 0");
}

void Application::updateEvents()
{
    while (m_window->pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
            m_running = false;
    }
}

void Application::update()
{
    const float dt = m_dtClock.restart().asSeconds();
    const sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_start = true;
    }

    if (!m_start)
    {
        if (!m_settings.randomGenerated)
        {
            m_board->updateInput(mousePos);
        }
    }
    else
    {
        m_timer += dt;

        if (m_timer >= m_settings.timeStep)
        {
            m_board->update();
            ++m_generation;
            m_timer = 0.0f;
        }

        m_infoText.setString(
            "Generation: " + std::to_string(m_generation) + 
            "\n\nPopulation: " + std::to_string(m_board->countAliveCells())
        );
    }
}

void Application::render()
{
    m_window->clear();

    m_board->render(*m_window);
    m_window->draw(m_infoText);
    
    m_window->display();
}

void Application::loadSettings()
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
                in >> m_settings.cellSize;
            }
            if (s == "# Board width")
            {
                in >> m_settings.boardWidth;
            }
            if (s == "# Board height")
            {
                in >> m_settings.boardHeight;
            }
            if (s == "# Initial patron random (1 yes, 0 not)")
            {
                in >> m_settings.randomGenerated;
            }
            if (s == "# Time step")
            {
                in >> m_settings.timeStep;
            }
        }
    }
}
