#include "BrickManager.h"
#include "GameManager.h"

BrickManager::BrickManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{
}

void BrickManager::createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    float leftEdge;
    if (cols % 2 == 0) 
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickWidth + (cols / 2.0f) * spacing);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            _bricks.emplace_back(x, y, brickWidth, brickHeight);
        }
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks) {
        brick.render(*_window);
    }
}

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction)
{
    int index = 0;
    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.

    std::vector<int> explodedBricks;

    for (auto& brick : _bricks)
    {
        index++;
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.
        
        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;
        
     
        // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
        // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector
        _gameManager->getSoundManager()->playSound(brickBreak); // Play brick breaking sound
        brick = _bricks.back();
        _bricks.pop_back();

        if (_gameManager->getPowerupManager()->getPowerupInEffect().first == explosiveBall)
        {
            for (int j = 0; j < _bricks.size(); j++)
            {
                if (j == index) continue; // Is already hit brick

                // Find distance between hit brick and brick indexed at j
                float distanceBetweenBricks = sqrt(pow(brickBounds.top - _bricks[j].getBounds().top, 2) + pow(brickBounds.left - _bricks[j].getBounds().left, 2));

                // If distance between hit brick and index j brick < 100 units
                if (distanceBetweenBricks <= EXPLOSION_RADIUS)
                {
                    // Destroy brick
                    _bricks[j] = _bricks.back();
                    _bricks.pop_back();
                    j--;
                }
            }
        }
        break;
    }
    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}