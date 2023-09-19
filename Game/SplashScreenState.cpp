#include "SplashScreenState.h"
#include "Global.h"

SplashScreenState::SplashScreenState(sf::RenderWindow* window) :
	State(window, GameState::Entry),
	alphaValue(0.f),
	fadeOut(false)
{
	if (!texture.loadFromFile(LOGO_TEXTURE))
		std::cout << "Fail to load: LOGO_TEXTURE" << std::endl;
}

SplashScreenState::~SplashScreenState()
{
}

void SplashScreenState::Load()
{
	alphaValue = 0.f;
	fadeOut = false;
	timer = 0.f;

	_logo.setTexture(texture);
	_logo.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	_logo.setColor(sf::Color(0, 0, 0, alphaValue));
	_logo.setPosition(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT);
}

void SplashScreenState::Update(float deltaTime)
{
	const float speed = 50.f;
	timer += deltaTime;

	if (!fadeOut)
	{
		alphaValue += speed * deltaTime;
		if (alphaValue >= 150)
		{
			alphaValue = 150;
			fadeOut = true;
		}
		_logo.setColor(sf::Color(255, 255, 255, alphaValue));
	}
	else if (fadeOut)
	{
		alphaValue -= speed * deltaTime;
		if (alphaValue <= 0)
		{
			alphaValue = 0;
		}
		_logo.setColor(sf::Color(255, 255, 255, alphaValue));
	}
}

void SplashScreenState::Render(sf::RenderTarget* target)
{

	target->draw(_logo);
}

GameState SplashScreenState::UpdateState(float deltaTime)
{
	Update(deltaTime);
	if (timer >= 7)
		return GameState::Menu;
	return GameState::Entry;
}

GameState SplashScreenState::GetState()
{
	return GameState::Entry;
}

void SplashScreenState::Unload()
{
}
