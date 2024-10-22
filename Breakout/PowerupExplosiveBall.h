#pragma once

#include "PowerupManager.h"

class PowerupExplosiveBall : public PowerupBase
{
public:
	PowerupExplosiveBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupExplosiveBall();

	std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};

