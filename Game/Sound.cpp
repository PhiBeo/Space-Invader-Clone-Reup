#include "Sound.h"
#include "Global.h"

Sound* Sound::instance = 0;

Sound* Sound::getInstance()
{
    if (instance == 0)
    {
        instance = new Sound();
    }

    return instance;
}

Sound::~Sound()
{
    _sound.resetBuffer();
    _soundBuffers.clear();

    delete instance;
}

void Sound::buttonClick()
{
    _sound.setBuffer(_soundBuffers[0]);
    _sound.play();
}

void Sound::shooting()
{
    _sound.setBuffer(_soundBuffers[1]);
    _sound.play();
}

void Sound::playerDie()
{
    _sound.setBuffer(_soundBuffers[2]);
    _sound.play();
}

void Sound::enemyDie()
{
    _sound.setBuffer(_soundBuffers[3]);
    _sound.play();
}

void Sound::setSFXValue(float value)
{
    _sound.setVolume(value);
}

Sound::Sound() 
{
    sf::SoundBuffer uiclick;
    sf::SoundBuffer shoot;
    sf::SoundBuffer playerDie;
    sf::SoundBuffer enemyDie;

    if (!uiclick.loadFromFile(UI_CLICK))
        std::cout << "fail to load: UI_CLICK" << std::endl;
    if(!shoot.loadFromFile(SHOOT_SOUND))
        std::cout << "fail to load: SHOOT_SOUND" << std::endl;
    if (!playerDie.loadFromFile(PLAYER_DIE))
        std::cout << "fail to load: PLAYER_DIE" << std::endl;
    if (!enemyDie.loadFromFile(ENEMY_DIE))
        std::cout << "fail to load: ENEMY_DIE" << std::endl;

    _soundBuffers.push_back(uiclick);
    _soundBuffers.push_back(shoot);
    _soundBuffers.push_back(playerDie);
    _soundBuffers.push_back(enemyDie);
   
}
