#pragma once
#include "Enums.h"
#include "SFML/Graphics.hpp"

class State
{
public:
	State(sf::RenderWindow* window, GameState state) : _window(window), _state(state) {}

	virtual void Load() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderTarget* target) = 0;
	virtual GameState UpdateState(float deltaTime) = 0;
	virtual GameState GetState() = 0;
	virtual void Unload() = 0;

protected:
	sf::RenderWindow* _window;
	
private:
	GameState _state;
};

