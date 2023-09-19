#include "Button.h"
#include "Global.h"
#include "Sound.h"

Button::Button(sf::RenderWindow* window, sf::Vector2f position) :
	window(window),
    _position(position)
{
	if (!font.loadFromFile(DEFAULT_FONT))
		throw("Fail to load: DEFAULT_FONT");

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(_position);

	if (!texture.loadFromFile(BUTTON_EMPTY))
		throw("Fail to load: BUTTON_EMPTY");

	button.setTexture(texture);


	isPress = false;
	highlight = sf::Color::Red;
}

Button::~Button()
{
}

sf::Vector2f Button::getPosition()
{
    return _position;
}

void Button::setPosition(sf::Vector2f position)
{
	_position = position;
}

void Button::setTextColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::setButtonColor(sf::Color color)
{
	button.setColor(color);
}

void Button::setString(std::string string)
{
	text.setString(string);

	textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

void Button::setHighlight(sf::Color color)
{
	highlight = color;
}

bool Button::isPressed()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		isPress = false;
		setButtonColor(sf::Color::White);
	}

	if (sf::Mouse::getPosition(*window).x >= _position.x - BUTTON_WIDTH / 2 && sf::Mouse::getPosition(*window).x <= _position.x + BUTTON_WIDTH / 2 &&
		sf::Mouse::getPosition(*window).y >= _position.y - BUTTON_HEIGHT / 2 && sf::Mouse::getPosition(*window).y <= _position.y + BUTTON_HEIGHT / 2)
	{
		setButtonColor(highlight);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isPress)
		{
			isPress = true;
			setButtonColor(sf::Color::White);
			Sound* click = Sound::getInstance();
			click->buttonClick();
			return true;
		}
	}

	return false;
}

void Button::drawButton(sf::RenderTarget* target)
{
	button.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	button.setPosition(_position);
	text.setPosition(_position);

	target->draw(button);
	target->draw(text);
}
