#pragma once
#include "SFML/Graphics.hpp"

class Slider
{
public:
	Slider(sf::RenderWindow* window, sf::Vector2f position = sf::Vector2f(0,0));
	~Slider();

	float getValue();
	void setValueLimit(float min, float max);
	void setTextColor(sf::Color color);
	void setSliderString(std::string title);

	void Logic();

	void Render(sf::RenderTarget* target);

private:
	float _value;
	float _minValue;
	float _maxValue;
	sf::Vector2f _position;

	sf::RenderWindow* window;

	sf::Texture _barTexure;
	sf::Texture _emptyBarTexture;
	sf::Texture _sliderTexture;

	sf::Sprite _barSprite;
	sf::Sprite _emptyBarSprite;
	sf::Sprite _sliderSprite;

	float barHeight;
	bool isHold;
	bool outOfRange;

	sf::Text text;
	sf::Font font;
	sf::FloatRect textRect;
};

