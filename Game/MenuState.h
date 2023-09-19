#pragma once
#include "State.h"
#include "Button.h"

class MenuState : public State
{
public:
	MenuState(sf::RenderWindow* window);
	virtual ~MenuState();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	GameState UpdateState(float deltaTime) override;
	GameState GetState() override;
	void Unload() override;

private:
	Button _start;
	Button _quit;
	Button _howToPlay;
	Button _setting;

	sf::Font font;
};

