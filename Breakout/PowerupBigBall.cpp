#include "PowerupBigBall.h"

PowerupBigBall::PowerupBigBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(extraBallEffectsColour); 
}

PowerupBigBall::~PowerupBigBall()
{

}

std::pair<POWERUPS, float> PowerupBigBall::applyEffect()
{
    _ball->setRadius(25.f, 5.0f);
    return { bigBall, 5.0f };
}