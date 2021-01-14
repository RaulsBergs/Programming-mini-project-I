#include "Tank.h"
#include "CollisionDetector.h"

Tank::Tank(sf::Texture const& t_texture, std::vector<sf::Sprite>& t_wallSprites)
	: m_texture(t_texture)
	, m_wallSprites(t_wallSprites)
{
	initSprites(m_tankBase.getPosition());
}

void Tank::update(double dt)
{
	m_previousPosition = m_tankBase.getPosition();

	handleKeyInput();

	float x_pos = m_tankBase.getPosition().x + ((cos( m_tankRotation * MathUtility::DEG_TO_RAD) * m_speed) * (dt / 1000));
	
	float y_pos = m_tankBase.getPosition().y + ((sin(m_tankRotation * MathUtility::DEG_TO_RAD) * m_speed) * (dt / 1000));

	float turretx_pos = m_tankBase.getPosition().x;

	float turrety_pos = m_tankBase.getPosition().y;

	m_tankBase.setPosition(sf::Vector2f{x_pos,y_pos});
	m_turret.setPosition(sf::Vector2f(turretx_pos, turrety_pos));

	if (checkWallCollision())
	{
		deflect();
	}
}

void Tank::render(sf::RenderWindow& window)
{
	window.draw(m_tankBase);
	window.draw(m_turret);
}

void Tank::setPosition(TankData t_tankdata)
{
	m_tankBase.setPosition(t_tankdata.m_position);
	m_turret.setPosition(t_tankdata.m_position);
}


void Tank::initSprites(sf::Vector2f const& pos)
{
	// Initialise the tank base

	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_tankBase.setPosition(pos);
	m_tankBase.setRotation(m_tankRotation);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	m_turret.setPosition(pos);
	m_turret.setRotation(m_tankRotation);
}

bool Tank::checkWallCollision()
{
	for (sf::Sprite const& sprite : m_wallSprites)
	{
		// Checks if either the tank base or turret has collided with the current wall sprite.
		if (CollisionDetector::collision(m_turret, sprite) ||
			CollisionDetector::collision(m_tankBase, sprite))
		{
			return true;
		}
	}
	return false;
}

void Tank::deflect()
{
	// In case tank was rotating.
	adjustRotation();

	// If tank was moving.
	if (m_speed != 0)
	{
		// Temporarily disable turret rotations on collision.
		m_enableRotation = false;
		// Back up to position in previous frame.
		m_tankBase.setPosition(m_previousPosition);
		// Apply small force in opposite direction of travel.
		if (m_previousSpeed < 0)
		{
			m_speed = 8;
			m_enableRotation = true;
		}
		else
		{
			m_speed = -8;
			m_enableRotation = true;
		}
	}
}

void Tank::adjustRotation()
{
	// If tank was rotating...
	if (m_tankRotation != m_previousTankRotation)
	{
		// Work out which direction to rotate the tank base post-collision.
		if (m_tankRotation > m_previousTankRotation)
		{
			m_tankRotation = m_previousTankRotation - 1;
		}
		else
		{
			m_tankRotation = m_previousTankRotation + 1;
		}
	}
	// If turret was rotating while tank was moving
	if (m_turretRotation != m_previousTurretRotation)
	{
		// Set the turret rotation back to it's pre-collision value.
		m_turretRotation = m_previousTurretRotation;
	}
}

////////////////////////////////////////////////////////////
void Tank::increaseSpeed()
{
	if (m_speed < 100.0)
	{
		m_speed += 3;
	}
}

////////////////////////////////////////////////////////////
void Tank::decreaseSpeed()
{
	if (m_speed > -100.0)
	{
		m_speed -= 3;
	}
}

////////////////////////////////////////////////////////////
void Tank::increaseRotation()
{
	if (m_enableRotation == true)
	{
		m_previousTankRotation = m_tankRotation;
		m_previousTurretRotation = m_turretRotation;

		m_tankRotation += 3;
		m_turretRotation += 3;
		if (m_tankRotation == 360.0)
		{
			m_tankRotation = 0;
		}
		if (m_turretRotation == 360.0)
		{
			m_turretRotation = 0;
		}
		m_tankBase.setRotation(m_tankRotation);
		m_turret.setRotation(m_turretRotation);
	}	
}

////////////////////////////////////////////////////////////
void Tank::decreaseRotation()
{
	if (m_enableRotation)
	{
		m_previousTankRotation = m_tankRotation;
		m_previousTurretRotation = m_turretRotation;

		m_tankRotation -= 3;
		m_turretRotation -= 3;
		if (m_tankRotation == 0.0)
		{
			m_tankRotation = 359.0;
		}
		if (m_turretRotation == 0.0)
		{
			m_turretRotation = 359.0;
		}
		m_tankBase.setRotation(m_tankRotation);
		m_turret.setRotation(m_turretRotation);
	}
}

void Tank::handleKeyInput()
{
	// check if the event is a a mouse button release
	if (sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Tank::increaseSpeed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Tank::decreaseSpeed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Tank::decreaseRotation();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Tank::increaseRotation();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			Tank::decreaseTurretRotation();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			Tank::decreaseTurretRotation();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			Tank::centreTurret();
		}
	}
}

void Tank::increaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation;

	m_turretRotation += 3;
	if (m_turretRotation == 360.0)
	{
		m_turretRotation = 0;
	}
	m_turret.setRotation(m_turretRotation);
}

void Tank::decreaseTurretRotation()
{
	m_previousTurretRotation = m_turretRotation;

	m_turretRotation -= 3;
	if (m_turretRotation == 0.0)
	{
		m_turretRotation = 359.0;
	}
	m_turret.setRotation(m_turretRotation);
}

void Tank::centreTurret()
{
	m_turretRotation = m_tankRotation;
	m_turret.setRotation(m_turretRotation);
}
