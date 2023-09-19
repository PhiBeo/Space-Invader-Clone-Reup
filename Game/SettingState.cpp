#include "SettingState.h"
#include "Global.h"
#include "DrawText.h"
#include "Sound.h"

SettingState::SettingState(sf::RenderWindow* window) :
	State(window, GameState::Intruction),
	_return(window, sf::Vector2f(SCREEN_WIDTH - BUTTON_WIDTH / 1.5, SCREEN_HEIGHT - BUTTON_HEIGHT)),
	_sfx(window, sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2))
{
	sound = Sound::getInstance();
	if (!font.loadFromFile(GAME_FONT))
		std::cout << "fail to load: GAME_FONT" << std::endl;
}

SettingState::~SettingState()
{
}

void SettingState::Load()
{
	_return.setString("Back");
	_sfx.setSliderString("SFX");
}

void SettingState::Update(float deltaTime)
{
	_sfx.Logic();
	sound->setSFXValue(_sfx.getValue());
}

void SettingState::Render(sf::RenderTarget* target)
{
	drawText("Setting", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_OFFSET * 1.5), 25, target, font);

	_return.drawButton(target);
	_sfx.Render(target);
}

GameState SettingState::UpdateState(float deltaTime)
{
	Update(deltaTime);
	if (_return.isPressed())
		return GameState::Menu;

	return GameState::Settting;
}

GameState SettingState::GetState()
{
	return GameState::Settting;
}

void SettingState::Unload()
{
}
