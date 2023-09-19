#include "DrawText.h"

void drawText(std::string string, sf::Vector2f position, int size, sf::RenderTarget* target, sf::Font font,sf::Color color)
{

	sf::Text text;
	text.setFont(font);
	text.setString(string);
	text.setPosition(position);
	text.setFillColor(color);
	text.setCharacterSize(size);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(1);
	
	sf::FloatRect textRect;
	textRect = text.getGlobalBounds();

	sf::RectangleShape box;
	box.setSize(sf::Vector2f(textRect.width, textRect.height));
	text.setOrigin(box.getSize().x / 2, box.getSize().y / 2);

	target->draw(text);
}
