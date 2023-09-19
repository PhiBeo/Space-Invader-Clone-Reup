#include "MenuState.h"
#include "Global.h"
#include "DrawText.h"

MenuState::MenuState(sf::RenderWindow* window) :
	State(window, GameState::Menu),
	_start(_window, sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + BUTTON_HEIGHT * 2)),
	_quit(_window, sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + BUTTON_HEIGHT * 2 + TEXT_SIZE * 6)),
	_howToPlay(_window, sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + BUTTON_HEIGHT * 2 + TEXT_SIZE * 2)),
	_setting(_window, sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + BUTTON_HEIGHT * 2 + TEXT_SIZE * 4))
{
	if (!font.loadFromFile(DEFAULT_FONT))
		throw("Fail to load: DEFAULT_FONT");
}

MenuState::~MenuState()
{
}

void MenuState::Load()
{
	_start.setString("Start Game");
	_howToPlay.setString("Intruction");
	_setting.setString("Setting");
	_quit.setString("Quit Game");
}

void MenuState::Update(float deltaTime)
{
}

void MenuState::Render(sf::RenderTarget* target)
{
	_start.drawButton(target);
	_howToPlay.drawButton(target);
	_setting.drawButton(target);
	_quit.drawButton(target);

	drawText(GAME_NAME, sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT - BUTTON_HEIGHT * 2), 50, target, font);
}

GameState MenuState::UpdateState(float deltaTime)
{
	Update(deltaTime);
	if (_start.isPressed())
		return GameState::Run;
	else if (_quit.isPressed())
		return GameState::Exit;
	else if (_howToPlay.isPressed())
		return GameState::Intruction;
	else if (_setting.isPressed())
		return GameState::Settting;
	return GameState::Menu;
}

GameState MenuState::GetState()
{
	return GameState::Menu;
}

void MenuState::Unload()
{
}
