#pragma once
#include "SFML/Graphics.hpp"
#include "Tank.h"
#include <cstdlib>


class Bullet
{
public:
	//data members
	sf::Sprite m_bulletSprite;
	sf::Texture m_bulletTexture;
	sf::Vector2f m_bulletPosition;
	double m_bulletSpeed;
	float m_bulletRotation;
	bool m_renderBullet{ false };
	//function members
	void update(double dt, Tank& t_tank);
	void render(sf::RenderWindow& window);

	Bullet();
	void handleKeyInput(double dt);
	void initBullet(Tank& t_tank);
	void shootBullet(double dt);
	void checkOffScreen();
};

