#include "Slider.h"
#include "Global.h"

Slider::Slider(sf::RenderWindow* window, sf::Vector2f position) :
    window(window),
    _minValue(0.f),
    _maxValue(100.f),
    _value(_maxValue),
    _position(position),
    barHeight(10.f),
    outOfRange(false),
    isHold(false)
{
    //texture and sprite
    if(!_sliderTexture.loadFromFile(VOLUMN_SLIDER))
        std::cout << "Fail to load: VOLUMN_SLIDER" << std::endl;
    if(!_barTexure.loadFromFile(VOLUMN_BAR))
        std::cout << "Fail to load: VOLUMN_BAR" << std::endl;
    if(!_emptyBarTexture.loadFromFile(VOLUMN_BAR_EMPTY))
        std::cout << "Fail to load: VOLUMN_BAR_EMPTY" << std::endl;

    _sliderSprite.setTexture(_sliderTexture);
    _sliderSprite.setOrigin(_sliderTexture.getSize().x / 2, _sliderTexture.getSize().y / 2);
    _sliderSprite.setPosition(sf::Vector2f(_position.x + _barTexure.getSize().x / 2, position.y));

    _barSprite.setTexture(_barTexure);
    _barSprite.setOrigin(_barTexure.getSize().x / 2, _barTexure.getSize().y / 2);
    _barSprite.setPosition(_position);

    _emptyBarSprite.setTexture(_emptyBarTexture);
    _emptyBarSprite.setOrigin(_emptyBarTexture.getSize().x / 2, _emptyBarTexture.getSize().y / 2);
    _emptyBarSprite.setPosition(_position);


    //text
    if (!font.loadFromFile(DEFAULT_FONT))
        std::cout << "Fail to load: DEFAULT_FONT" << std::endl;

    text.setFont(font);
    text.setCharacterSize(TEXT_SIZE / 2);
    text.setFillColor(sf::Color::Black);
    text.setString("No Message");

    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    text.setPosition(sf::Vector2f(_position.x - _barTexure.getSize().x / 2 - textRect.width / 1.5f, _position.y));
}

Slider::~Slider()
{
}

float Slider::getValue()
{
    return _value;
}

void Slider::setValueLimit(float min, float max)
{
    _minValue = min;
    _maxValue = max;
}

void Slider::setTextColor(sf::Color color)
{
    text.setFillColor(color);
}

void Slider::setSliderString(std::string title)
{
    text.setString(title);

    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(_position.x - _barTexure.getSize().x / 2 - textRect.width / 1.5f, _position.y));
}

void Slider::Logic()
{
    if (isHold && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
        isHold = false;

    if (sf::Mouse::getPosition(*window).x >= _sliderSprite.getPosition().x - _sliderTexture.getSize().x / 2 &&
        sf::Mouse::getPosition(*window).x <= _sliderSprite.getPosition().x + _sliderTexture.getSize().x / 2 &&
        sf::Mouse::getPosition(*window).y >= _sliderSprite.getPosition().y - _sliderTexture.getSize().y / 2 &&
        sf::Mouse::getPosition(*window).y <= _sliderSprite.getPosition().y + _sliderTexture.getSize().y / 2)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isHold = true;
        }
    }

    _value = _sliderSprite.getPosition().x - (_barSprite.getPosition().x - _barTexure.getSize().x / 2);

    if (_value < _minValue || _value > _maxValue)
        outOfRange = true;
    
    if (isHold && !outOfRange)
    {
        if (sf::Mouse::getPosition(*window).x > _barSprite.getPosition().x - _barTexure.getSize().x / 2 &&
            sf::Mouse::getPosition(*window).x < _barSprite.getPosition().x + _barTexure.getSize().x / 2)
        {
            _sliderSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, _sliderSprite.getPosition().y));
        }
    }
    if (isHold)
    {
        if (sf::Mouse::getPosition(*window).x < _barSprite.getPosition().x - _barTexure.getSize().x / 2)
        {
            _sliderSprite.setPosition(sf::Vector2f(_barSprite.getPosition().x - _barTexure.getSize().x / 2, _sliderSprite.getPosition().y));
            _value = _minValue;
        }
        else if (sf::Mouse::getPosition(*window).x > _barSprite.getPosition().x + _barTexure.getSize().x / 2)
        {
            _sliderSprite.setPosition(sf::Vector2f(_barSprite.getPosition().x + _barTexure.getSize().x / 2, _sliderSprite.getPosition().y));
            _value = _maxValue;
        }
    }

    _barSprite.setTextureRect(sf::IntRect(0, 0, _value, _barTexure.getSize().y));
    
    //std::cout << _value << std::endl; 
}

void Slider::Render(sf::RenderTarget* target)
{
    target->draw(text);
    target->draw(_emptyBarSprite);
    target->draw(_barSprite);
    target->draw(_sliderSprite);
}


