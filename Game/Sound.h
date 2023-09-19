#pragma once
#include "SFML/Audio.hpp"
class Sound
{
public:
	static Sound* getInstance();

	virtual ~Sound();

	void buttonClick();
	void shooting();
	void playerDie();
	void enemyDie();
	void setSFXValue(float value);

private:
	static Sound* instance;
	Sound();

	std::vector<sf::SoundBuffer> _soundBuffers;
	sf::Sound _sound;

};

