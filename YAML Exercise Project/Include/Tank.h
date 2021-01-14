#pragma once
#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include <Thor/Vectors.hpp>
#include "MathUtility.h"

/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:
	// A reference to the container of wall sprites.
	std::vector<sf::Sprite>& m_wallSprites;

	Tank(sf::Texture const& texture , std::vector<sf::Sprite>& t_wallSprites);
	void update(double dt);
	void render(sf::RenderWindow& window);
	void setPosition(TankData t_tankdata);

	/// <summary>
	/// @brief Checks for collisions between the tank and the walls.
	/// 
	/// </summary>
	/// <returns>True if collision detected between tank and wall.</returns>
	bool checkWallCollision();

	/// <summary>
	/// @brief Stops the tank if moving and applies a small increase in speed in the opposite direction of travel.
	/// If the tank speed is currently 0, the rotation is set to a value that is less than the previous rotation value
	///  (scenario: tank is stopped and rotates into a wall, so it gets rotated towards the opposite direction).
	/// If the tank is moving, further rotations are disabled and the previous tank position is restored.
	/// The tank speed is adjusted so that it will travel slowly in the opposite direction. The tank rotation 
	///  is also adjusted as above if necessary (scenario: tank is both moving and rotating, upon wall collision it's 
	///  speed is reversed but with a smaller magnitude, while it is rotated in the opposite direction of it's 
	///  pre-collision rotation).
	/// </summary>
	void deflect();

	void adjustRotation();

	/// <summary>
	/// @brief Increases the speed by 1, max speed is capped at 100.
	/// 
	/// </summary>
	void increaseSpeed();

	/// <summary>
	/// @brief Decreases the speed by 1, min speed is capped at -100.
	/// 
	/// </summary>
	void decreaseSpeed();

	/// <summary>
	/// @brief Increases the rotation by 1 degree, wraps to 0 degrees after 359.
	/// 
	/// </summary>
	void increaseRotation();

	/// <summary>
	/// @brief Decreases the rotation by 1 degree, wraps to 359 degrees after 0.
	/// 
	/// </summary>
	void decreaseRotation();

	/// <summary>
	/// @brief Processes control keys and applies speed/rotation as appropriate.
	/// </summary>
	void handleKeyInput();

	void increaseTurretRotation();

	void decreaseTurretRotation();

	void centreTurret();

	// The tank speed.
	double m_speed{ 2.0 };
	sf::Sprite m_turret;
	// The current rotation as applied to tank base.
	double m_tankRotation{ 90.0 };
private:
	const int M_MAXHIGHSPEED = 100, M_MAXLOWSPEED = 0;
	void initSprites(sf::Vector2f const& pos);
	sf::Sprite m_tankBase;

	sf::Texture const& m_texture;
	double m_turretRotation{m_tankRotation};
	bool m_enableRotation{true};
	sf::Vector2f m_previousPosition;
	float m_previousSpeed;
	double m_previousTankRotation;
	double m_previousTurretRotation;
};