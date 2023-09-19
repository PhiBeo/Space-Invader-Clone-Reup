#pragma once
#include "SFML/Graphics.hpp"
#include "MenuState.h"
#include "GameOverState.h"
#include "IntructionState.h"
#include "SettingState.h"
#include "RunState.h"
#include "SplashScreenState.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void GameInit();
	void GameRunning();
	void GameShutDown();

	void Load();
	void Update();
	void Render();
	void UpdateDeltaTime();

	void WindowPollEv();

private:
	sf::RenderWindow* _window;
	sf::Event ev;

	MenuState _menuState;
	GameOverState _gameoverState;
	IntructionState _instructionState;
	SettingState _settingState;
	RunState _runState;
	SplashScreenState _splashScreenState;

	sf::Clock dtClock;
	float deltaTime;

	GameState currentState;
	sf::Font font;
};

