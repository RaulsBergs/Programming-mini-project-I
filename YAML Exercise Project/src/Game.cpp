#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "SFML Playground", sf::Style::Default)
	, m_tankObj(m_spriteSheetTexture,m_wallSprites)
{
	m_window.setVerticalSyncEnabled(true);

	if (!m_bgTexture.loadFromFile("./Resources/Images/Background.jpg"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_bgSprite.setTexture(m_bgTexture);

	if (!m_spriteSheetTexture.loadFromFile("./Resources/Images/SpriteSheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	int currentLevel = 1;
	// Will generate an exception if level loading fails.
	try
	{
		LevelLoader::load(currentLevel, m_level);
	}
	catch (std::exception& e)
	{
		std::cout << "Level Loading failure." << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}

	m_tankObj.setPosition(m_level.m_tankData);

	generateWalls();
}

////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(lag);
			lag -= MS_PER_UPDATE;
		}
		update(lag);

		render();
	}
}

////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{
	m_tankObj.update(dt);

	m_bullet.update(dt, m_tankObj);
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	// Render your sprites here....
	m_window.draw(m_bgSprite);
	for (int i = 0; i < m_wallSprites.size(); i++)
	{
		m_window.draw(m_wallSprites[i]);
	}
	m_tankObj.render(m_window);
	
	m_bullet.render(m_window);
	
	m_window.display();
}

void Game::generateWalls()
{
	sf::IntRect wallRect(2, 129, 33, 23);
	for (ObstacleData const& obstacle : m_level.m_obstacles)
	{
		sf::Sprite sprite;
		sprite.setTexture(m_spriteSheetTexture);
		sprite.setTextureRect(wallRect);
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(sprite);
	}
}



