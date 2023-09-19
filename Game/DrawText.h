#pragma once
#include "SFML/Graphics.hpp"
#include "Global.h"

void drawText(std::string string, sf::Vector2f position, int size ,sf::RenderTarget* target, sf::Font _font,sf::Color color = sf::Color(sf::Color::White));