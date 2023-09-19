#pragma once
#include "State.h"
#include "GameManager.h"
#include "Button.h"

enum class RunningState
{
	Play,
	Pause
};

class RunState : public State
{
public:
	RunState(sf::RenderWindow* window);
	virtual ~RunState();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	GameState UpdateState(float deltaTime) override;
	GameState GetState() override;
	void Unload() override;

	int getScore();
private:
	sf::Font font;

	GameManager* game;
	RunningState _currentState;
	bool _isPress;

	Button _quitGame;
	Button _mainMenu;

	sf::Texture _backgroundTexture;
	sf::Sprite _background;
};

