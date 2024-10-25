#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies
#include <iostream>

Ball::Ball(sf::RenderWindow* window, float velocity, float radius, GameManager* gameManager)
    : _window(window), _velocity(velocity), _radius(radius), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({ 1,1 })
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);

    for (int i = 0; i < 5; i++)
    {
        sf::CircleShape tempCircle;
        tempCircle.setRadius(RADIUS);
        tempCircle.setFillColor(sf::Color(255, 0, 255, 64));
        tempCircle.setPosition(0, 300);
        _ballTrail.push_back(tempCircle);
    }
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY)
            _velocity = VELOCITY;   // reset speed.
        else if (_radius != RADIUS)
        {
            _radius = RADIUS; // reset radius
            _sprite.setRadius(_radius);
            for (int i = 0; i < _ballTrail.size(); i++)
            {
                _ballTrail[i].setRadius(_radius);
            }
        }
        else
        {
            setFireBall(0);    // disable fireball
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }
    }

    // Ball Trail //
    if (!_ballTrail.empty())
        _ballTrail.front().setPosition(_sprite.getPosition());

    for (int i = 1; i < _ballTrail.size(); i++)
    {
        sf::Vector2f lastBallPos = _ballTrail[i - 1].getPosition();
        sf::Vector2f currentBallPos = _ballTrail[i].getPosition();

        _ballTrail[i].move((lastBallPos - currentBallPos) * (_velocity * 0.07f) * dt);
    }
    // ^Ball Trail ^//

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }




    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);


    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    boundaryCollision(position, _direction);


    // lose life bounce
    sf::Vector2u windowDimensions = _window->getSize();
    if (position.y > windowDimensions.y)
    {
        _sprite.setPosition(0, 300);
        _direction = { 1, 1 };
        _gameManager->loseLife();
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        paddleCollision(_sprite, _direction);
    }

    brickCollision(_sprite, _direction);
}

void Ball::render()
{
    for (int i = 0; i < _ballTrail.size(); i++)
    {
        _window->draw(_ballTrail[i]);
    }
    _window->draw(_sprite);
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * VELOCITY;
    _timeWithPowerupEffect = duration;
}

void Ball::setRadius(float radius, float duration)
{
    _radius = radius;
    _timeWithPowerupEffect = duration;
    _sprite.setRadius(_radius);

    for (auto& trails : _ballTrail)
        trails.setRadius(_radius);

}
void Ball::setFireBall(float duration)
{
    if (duration)
    {
        _isFireBall = true;
        _timeWithPowerupEffect = duration;
        return;
    }
    _isFireBall = false;
    _timeWithPowerupEffect = 0.f;
}



void Ball::paddleCollision(sf::CircleShape& sprite, sf::Vector2f& direction)
{
    // collision with paddle
    if (sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _gameManager->getSoundManager()->playSound(paddleBounce); // Play paddle bounce sound
        direction.y *= -1; // Bounce vertically
        float paddlePositionProportion = (sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        sprite.setPosition(sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * _radius);
    }
}

void Ball::boundaryCollision(sf::Vector2f position, sf::Vector2f& direction)
{
    sf::Vector2u windowDimensions = _window->getSize();
    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * _radius && direction.x > 0) || (position.x <= 0 && direction.x < 0))
    {
        direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && direction.y < 0)
    {
        direction.y *= -1;
    }

}

void Ball::brickCollision(sf::CircleShape sprite, sf::Vector2f& direction)
{
    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(sprite, direction);
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        direction.x *= -1; // Bounce horizontally

    }
    else if (collisionResponse == 2)
    {
        direction.y *= -1; // Bounce vertically
    }
}