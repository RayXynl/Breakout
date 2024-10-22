#include "PowerupExplosiveBall.h"

PowerupExplosiveBall::PowerupExplosiveBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(extraBallEffectsColour);
}

PowerupExplosiveBall::~PowerupExplosiveBall()
{

}

std::pair<POWERUPS, float> PowerupExplosiveBall::applyEffect()
{
    return { explosiveBall, 5.0f };
}