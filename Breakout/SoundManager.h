#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include <map>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void playSound(SOUNDS sound);
private:
	std::map<SOUNDS, sf::SoundBuffer> _gameSounds;
	sf::Sound _soundToPlay;
};

