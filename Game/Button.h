#pragma once
#include "SFML/Graphics.hpp"

class Button
{
public:
	Button(sf::RenderWindow* window , sf::Vector2f position);
	~Button();

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	void setTextColor(sf::Color color);
	void setButtonColor(sf::Color color);
	void setString(std::string string);
	void setHighlight(sf::Color color);

	bool isPressed();
	void drawButton(sf::RenderTarget* target);


private:
	sf::RenderWindow* window;

	sf::Vector2f _position;

	sf::Font font;
	sf::Text text;
	sf::FloatRect textRect;

	bool isPress;
	sf::Color highlight;

	sf::Texture texture;
	sf::Sprite button;
	
};

