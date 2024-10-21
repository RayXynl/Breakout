#include "PowerupManager.h"
#include "GameManager.h" // avoid cicular dependencies
#include "CONSTANTS.h"

PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball, GameManager* gameManager)
    : _window(window), _paddle(paddle), _ball(ball), _gameManager(gameManager)
{
 
}

PowerupManager::~PowerupManager()
{
    for (auto powerup : _powerups)
    {
        delete powerup;
    }
    _powerups.clear();
}

void PowerupManager::update(float dt)
{
    // tick down powerup effect time. Reset if elapsed.
    if (_powerupInEffect)
    {
        _powerupInEffect->second -= dt;
        if (_powerupInEffect->second <= 0)
        {
            _powerupInEffect.reset();
        }
    }


    for (auto it = _powerups.begin(); it != _powerups.end(); )
    {
        checkCollision();
        
        // Delete powerups queued for removal
        (*it)->update(dt);
        if (!(*it)->isAlive())
        {
            delete* it;
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::render()
{
    for (auto& powerup : _powerups)
    {
        powerup->render();
    }
}

void PowerupManager::spawnPowerup()
{
    switch (rand() % 7)
    {
    case 0:
        _powerups.push_back(new PowerupBigPaddle(_window, _paddle, _ball));
        break;
    case 1:
        _powerups.push_back(new PowerupSlowBall(_window, _paddle, _ball));
        break;
    case 2:
        _powerups.push_back(new PowerupFastBall(_window, _paddle, _ball));
        break;
    case 3:
        _powerups.push_back(new PowerupSmallPaddle(_window, _paddle, _ball));
        break;
    case 4:
        _powerups.push_back(new PowerupFireBall(_window, _paddle, _ball));
        break;
    case 5:
        _powerups.push_back(new PowerupBigBall(_window, _paddle, _ball));
       break;
    case 6:
        _powerups.push_back(new PowerupSmallBall(_window, _paddle, _ball));
        break;
    case 7:
        break;
    }

}

void PowerupManager::checkCollision()
{
    for (auto& powerups : _powerups)
    {
        if (powerups->checkCollisionWithPaddle())
        {
            _powerupInEffect = powerups->applyEffect();
            powerups->setAlive(false);
            _gameManager->getSoundManager()->playSound(powerup);
        }
    }
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerups.size();
}

std::pair<POWERUPS, float> PowerupManager::getPowerupInEffect()
{
    if (!_powerupInEffect) return { none, 0.f };
    return *_powerupInEffect;
}
