#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "LevelLoader.h"
#include "Tank.h"
#include "Bullet.h"

/// <summary>
/// @author RP
/// @date September 2020
/// @version 1.0
/// 
/// </summary>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML. 
/// Example usage:
///		Game game;
///		game.run();
/// </summary>

class Game
{
public:
	/// <summary>
	/// @brief Default constructor that initialises the SFML window, 
	///   and sets vertical sync enabled. 
	/// </summary>
	Game();

	/// <summary>
	/// @brief the main game loop.
	/// 
	/// A complete loop involves processing SFML events, updating and drawing all game objects.
	/// The actual elapsed time for a single game loop results (lag) is stored. If this value is 
	///  greater than the notional time for one loop (MS_PER_UPDATE), then additional updates will be 
	///  performed until the lag is less than the notional time for one loop.
	/// The target is one update and one render cycle per game loop, but slower PCs may 
	///  perform more update than render operations in one loop.
	/// </summary>
	void run();

protected:
	/// <summary>
	/// @brief Placeholder to perform updates to all game objects.
	/// </summary>
	/// <param name="time">update delta time</param>
	void update(double dt);

	/// <summary>
	/// @brief Draws the background and foreground game objects in the SFML window.
	/// The render window is always cleared to black before anything is drawn.
	/// </summary>
	void render();

	/// <summary>
	/// @brief Checks for events.
	/// Allows window to function and exit. 
	/// Events are passed on to the Game::processGameEvents() method.
	/// </summary>	
	void processEvents();

	/// <summary>
	/// @brief Handles all user input.
	/// </summary>
	/// <param name="event">system event</param>
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;

	/// <summary>
	/// @brief Creates the wall sprites and loads them into a vector.
	/// Note that sf::Sprite is considered a light weight class, so 
	///  storing copies (instead of pointers to sf::Sprite) in std::vector is acceptable.
	/// </summary>
	void generateWalls();

	//Non limiting array storing sprites
	std::vector<sf::Sprite>  m_sprites;

	// Wall sprites
	std::vector<sf::Sprite> m_wallSprites;

	// A texture for the sprite sheet
	sf::Texture m_spriteSheetTexture;

	// Background sprite and texture
	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;

	// Load the game level data.
	LevelData m_level;

	sf::Text playerScoreText;

	/// <summary>
	/// @brief Constructor that stores drawable state (texture, sprite) for the tank.
	/// Stores references to the texture and container of wall sprites. 
	/// Creates sprites for the tank base and turret from the supplied texture.
	/// </summary>
	/// <param name="t_texture">A reference to the sprite sheet texture</param>
	///< param name="t_wallSprites">A reference to the container of wall sprites</param>  
	Tank m_tankObj;

	Bullet m_bullet;

	sf::Sprite m_tankSprite;
};
