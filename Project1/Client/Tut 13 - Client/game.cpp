#include "game.h"

game::game() :
	m_window{ sf::VideoMode{ 800u, 600u, 32u }, "Basic game" },
	m_exitgame{ false },myClient("127.0.0.1", 1111)
{
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		throw std::exception("Server Connection Failed");
	}

	m_player.setFillColor(sf::Color::Red);
	m_player.setRadius(30.0f);
	m_player.setPosition(400.0f, 300.0f);
}

game::~game()
{

}

void game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // Run as many times as possible
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Run at a minimum of 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // Run as many times as possible
	}
}

void game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // check if the close window button is clicked on.
		{
			m_window.close();
		}
	}
}

void game::update(sf::Time t_deltaTime)
{
	if (m_exitgame)
	{
		m_window.close();
	}
}

void game::render()
{
	m_window.clear();

	m_window.draw(m_player);

	m_window.display();
}

std::string game::returnPos()
{
	return std::to_string(m_player.getPosition().x) + " " + std::to_string(m_player.getPosition().y);
}
