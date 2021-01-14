#include "Bullet.h"

void Bullet::update(double dt, Tank& t_tank)
{
	if (m_renderBullet == false)
	{
		Bullet::initBullet(t_tank);
	}
	handleKeyInput(dt);
	if (m_renderBullet == true)
	{
		shootBullet(dt);
	    checkOffScreen();
	}
}

void Bullet::render(sf::RenderWindow& window)
{
	if (m_renderBullet == true)
	{
		window.draw(m_bulletSprite);
	}
}

Bullet::Bullet()
{
	m_bulletRotation = 0;
	m_bulletSpeed = ((rand()% 1000) + 500);
	m_bulletPosition = { 0.0f,0.0f };
	if (!m_bulletTexture.loadFromFile("./Resources/Images/SpriteSheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	m_bulletSprite.setTexture(m_bulletTexture);
	sf::IntRect baseRect(8, 177, 12, 184);
	m_bulletSprite.setTextureRect(baseRect);
	m_bulletSprite.setOrigin(baseRect.width / 3.2, (baseRect.height / 30.0));
	m_bulletSprite.setPosition(m_bulletPosition);
	m_bulletSprite.setRotation(m_bulletRotation);
}

void Bullet::handleKeyInput(double dt)
{
	// check if the event is a a key button press
	if (sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_renderBullet = true;
			Bullet::shootBullet(dt);
		}
	}
}

void Bullet::initBullet(Tank& t_tank)
{
	m_bulletPosition = t_tank.m_turret.getPosition();
	m_bulletRotation = t_tank.m_turret.getRotation();

	m_bulletSprite.setRotation(m_bulletRotation - 90);
	m_bulletSprite.setPosition(m_bulletPosition.x, m_bulletPosition.y);
}

void Bullet::shootBullet(double dt)
{
	//m_renderBullet = true;
	float x_pos = m_bulletSprite.getPosition().x + ((cos(m_bulletRotation * MathUtility::DEG_TO_RAD) * m_bulletSpeed) * (dt / 1000));

	float y_pos = m_bulletSprite.getPosition().y + ((sin(m_bulletRotation * MathUtility::DEG_TO_RAD) * m_bulletSpeed) * (dt / 1000));

	m_bulletPosition = { x_pos , y_pos };
	m_bulletSprite.setPosition(m_bulletPosition);
}

void Bullet::checkOffScreen()
{
	if (m_bulletPosition.x < 0 || m_bulletPosition.x > 1500 
		|| m_bulletPosition.y > 1000 || m_bulletPosition.y < 0)
	{
		m_renderBullet = false;
	}
}
