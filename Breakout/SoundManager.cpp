#include "SoundManager.h"
#include <iostream>
SoundManager::SoundManager()
{
	sf::SoundBuffer tempBuffer;
	// Load paddle bounc sound
	tempBuffer.loadFromFile("Sounds/paddle_bounce.mp3");
	_gameSounds[paddleBounce] = tempBuffer;
	// Load power up sound
	tempBuffer.loadFromFile("Sounds/powerup.mp3");
	_gameSounds[powerup] = tempBuffer;
	// Load life lost sound
	tempBuffer.loadFromFile("Sounds/life_lost.mp3");
	_gameSounds[lifeLost] = tempBuffer;
	// Load game over sound
	tempBuffer.loadFromFile("Sounds/game_over.mp3");
	_gameSounds[gameOver] = tempBuffer;
	// Load brick breaking sound
	tempBuffer.loadFromFile("Sounds/break_brick.mp3");
	_gameSounds[brickBreak] = tempBuffer;
}

SoundManager::~SoundManager()
{
	_soundToPlay.resetBuffer();
}

void SoundManager::playSound(SOUNDS sound)
{
	if (_gameSounds.find(sound) != _gameSounds.end())
	{
		_soundToPlay.setBuffer(_gameSounds[sound]);
		_soundToPlay.play();
		std::cout << "sound play";
	}
}