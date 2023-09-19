#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include "Button.h"

class GameOverState : public State
{
public:
	GameOverState(sf::RenderWindow* window);
	virtual ~GameOverState();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	GameState UpdateState(float deltaTime) override;
	GameState GetState() override;
	void Unload() override;

	void setScore(int score);

private:
	Button _mainMenu;
	Button _restart;

	sf::Font font;
	int gameScore;
};

