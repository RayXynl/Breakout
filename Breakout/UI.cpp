#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager) 
	: _window(window), _gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Red);	
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(800, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_powerupText.setOutlineColor(sf::Color::Black);
	_powerupText.setOutlineThickness(1.0f);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	_progressBar.setPosition(780, 10);
	_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH, PROGRESSBAR_HEIGHT));
	_progressBar.setFillColor(sf::Color::Red);
	_progressBar.setOutlineColor(sf::Color::White);
	_progressBar.setOutlineThickness(1.0f);
}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	switch (powerup.first)
	{
	case bigPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big paddle" + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small paddle " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow ball" + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast ball " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire ball" + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		break;
	case bigBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big ball " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		break;	
	case smallBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small ball " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		break;
	case explosiveBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("explosive ball " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_powerupText.setString("");
		break;
	}
}

void UI::updatePowerupProgressBar(std::pair<POWERUPS, float> powerup)
{
	switch (powerup.first)
	{
	case bigPaddle:
	
		_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH * powerup.second / 5.0f, PROGRESSBAR_HEIGHT));
		_progressBar.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH * powerup.second / 5.0f, PROGRESSBAR_HEIGHT));
		_progressBar.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH * powerup.second / 5.0f, PROGRESSBAR_HEIGHT));
		_progressBar.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH * powerup.second / 5.0f, PROGRESSBAR_HEIGHT));
		_progressBar.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH * powerup.second / 5.0f, PROGRESSBAR_HEIGHT));
		_progressBar.setFillColor(extraBallEffectsColour);
		break;
	case bigBall:
		_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH * powerup.second / 5.0f, PROGRESSBAR_HEIGHT));
		_progressBar.setFillColor(extraBallEffectsColour);
		break;	
	case smallBall:
		_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH * powerup.second / 5.0f, PROGRESSBAR_HEIGHT));
		_progressBar.setFillColor(extraBallEffectsColour);
		break;
	case explosiveBall:
		_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH * powerup.second / 5.0f, PROGRESSBAR_HEIGHT));
		_progressBar.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_progressBar.setSize(sf::Vector2f(PROGRESSBAR_WIDTH, PROGRESSBAR_HEIGHT));
		_progressBar.setFillColor(sf::Color::Black);
		break;
	}
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	_window->draw(_progressBar);
	_window->draw(_powerupText);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
	
}