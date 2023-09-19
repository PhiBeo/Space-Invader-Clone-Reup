#include "GameOverState.h"
#include "Global.h"
#include "DrawText.h"

GameOverState::GameOverState(sf::RenderWindow* window) :
	State(window, GameState::Gameover),
	_mainMenu(window, sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + BUTTON_HEIGHT * 2)),
	_restart(window, sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + BUTTON_HEIGHT * 2 + TEXT_SIZE * 2))
{
	if (!font.loadFromFile(GAME_FONT))
		std::cout << "fail to load: GAME_FONT" << std::endl;
}

GameOverState::~GameOverState()
{
}

void GameOverState::Load()
{
	_restart.setString("Restart");
	_mainMenu.setString("Main Menu");
}

void GameOverState::Update(float deltaTime)
{
}

void GameOverState::Render(sf::RenderTarget* target)
{
	drawText("You're Dead", sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_OFFSET * 2), 25, target, font);
	drawText("You score is: " + std::to_string(gameScore), sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_OFFSET * 4), 25, target, font);
	
	_restart.drawButton(target);
	_mainMenu.drawButton(target);
}

GameState GameOverState::UpdateState(float deltaTime)
{
	Update(deltaTime);
	if (_restart.isPressed())
		return GameState::Run;
	else if (_mainMenu.isPressed())
		return GameState::Menu;

	return GameState::Gameover;
}

GameState GameOverState::GetState()
{
	return GameState::Gameover;
}

void GameOverState::Unload()
{
}

void GameOverState::setScore(int score)
{
	gameScore = score;
}
