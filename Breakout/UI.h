#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "CONSTANTS.h"
#include "PowerupManager.h"

class GameManager;

class UI
{
public:
	UI(sf::RenderWindow* window, int lives, GameManager* gameManager);
	~UI();

	void updatePowerupText(std::pair<POWERUPS, float>);
	void updatePowerupProgressBar(std::pair<POWERUPS, float>);
	void lifeLost(int lives);
	void render();

private:
	GameManager* _gameManager;
	
	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _powerupText;

	std::vector<sf::CircleShape> _lives;
	sf::RectangleShape _progressBar;



	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
	static constexpr float PROGRESSBAR_WIDTH = 200.0f;
	static constexpr float PROGRESSBAR_HEIGHT = 35.0f;
};

