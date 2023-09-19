#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "Slider.h"

class Sound;

class SettingState : public State
{
public:
	SettingState(sf::RenderWindow* window);
	virtual ~SettingState();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	GameState UpdateState(float deltaTime) override;
	GameState GetState() override;
	void Unload() override;

private:
	Button _return;
	Slider _sfx;

	Sound* sound;
	sf::Font font;
};

