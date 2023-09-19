#pragma once
#include "State.h"

class SplashScreenState : public State
{
public:
	SplashScreenState(sf::RenderWindow* window);
	virtual ~SplashScreenState();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	GameState UpdateState(float deltaTime) override;
	GameState GetState() override;
	void Unload() override;

private:
	sf::Texture texture;
	sf::Sprite _logo;

	float alphaValue;
	bool fadeOut;
	float timer;
};

