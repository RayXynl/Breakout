#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, float radius, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setRadius(float radius, float duration);

    void paddleCollision(sf::CircleShape& sprite, sf::Vector2f& direction);
    void boundaryCollision(sf::Vector2f position, sf::Vector2f& direction);
    void brickCollision(sf::CircleShape sprite, sf::Vector2f& direction);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    float _radius;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager

    std::vector<sf::CircleShape> _ballTrail;
  
    static constexpr float RADIUS = 10.0f;
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

