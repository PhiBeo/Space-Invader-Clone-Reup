#pragma once
#include "SFML/Graphics.hpp"

class Entity
{
public:
	Entity() {}
	virtual ~Entity() {}

	virtual void Load() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderTarget* target) = 0;
	virtual void Unload() = 0;

};

