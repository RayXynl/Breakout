#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _soundManager(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);

    // Background
    _backgroundTexture.loadFromFile("william.jpg");
    _spriteBackground.setTexture(_backgroundTexture);
    _spriteBackground.setScale(sf::Vector2f(2.0f, 3.0f));
    
}

void GameManager::initialize()
{
    _lives = INITIAL_LIVES;
    _levelComplete = false;
    _powerupInEffect = { none, 0.0f };

    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, BALL_SPEED, BALL_RADIUS, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball, this);
    _ui = new UI(_window, _lives, this);
    _soundManager = new SoundManager();

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();

    _ui->updatePowerupText(_powerupInEffect);
    _ui->updatePowerupProgressBar(_powerupInEffect);
    _powerupInEffect.second -= dt;
    
    // Lives check
    if (_lives <= 0)
    {
        // Check for input to restart level
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            _masterText.setString("");
            initialize();
        }
        else
            return;
    }

    if (_levelComplete)
    {
        _masterText.setString("Level completed. \n Press Spacebar to start again");
        _masterText.setFillColor(sf::Color::Green);

        // Check for input to restart level
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            _masterText.setString("");
            initialize();
        }
        else
            return;
    }
  
    // Check for pause input
    pauseHandling(dt);

    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;

    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand() % SPAWN_CHANCE == 0) 
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);
    _paddle->moveToMouse(dt);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::pauseHandling(float dt)
{
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && _pauseHold <= 0.f)
    {
        _pause = !_pause;

        if (_pause)
            _masterText.setString("paused.");
        else
            _masterText.setString("");
      
        _pauseHold = PAUSE_TIME_BUFFER;
    }
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
    _soundManager->playSound(lifeLost);

    // Store Original Screen position
    sf::Vector2i ScreenPos = _window->getPosition();

    // Screen Shake
    for (int i = 0; i < 200; i++)
    {
        _window->setPosition(sf::Vector2i(ScreenPos.x + rand() % 25, ScreenPos.y + rand() % 25));
    }

    // Set screen position back to original after screen shake
    _window->setPosition(ScreenPos);

    if (_lives <= 0)
    {
        _soundManager->playSound(gameOver);
        _masterText.setString("Game over. \n Press Spacebar to start again");
        _masterText.setFillColor(sf::Color::Red);
    }
}

void GameManager::render()
{
    _window->draw(_spriteBackground);
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
SoundManager* GameManager::getSoundManager() const { return _soundManager; }
