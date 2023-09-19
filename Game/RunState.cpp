#include "RunState.h"
#include "DrawText.h"

RunState::RunState(sf::RenderWindow* window) :
	State(window, GameState::Run),
	game(nullptr),
	_currentState(RunningState::Play),
	_isPress(false),
	_quitGame(window, sf::Vector2f(SCREEN_WIDTH - BUTTON_WIDTH / 2, SCREEN_HEIGHT - BUTTON_HEIGHT / 2)),
	_mainMenu(window, sf::Vector2f(SCREEN_WIDTH - (BUTTON_WIDTH  + BUTTON_WIDTH / 2), SCREEN_HEIGHT - BUTTON_HEIGHT / 2))
{
	if (!font.loadFromFile(GAME_FONT))
		std::cout << "fail to load: GAME_FONT" << std::endl;
	if (!_backgroundTexture.loadFromFile(BACKGROUND))
		std::cout << "fail to load: BACKGROUND" << std::endl;
	_background.setTexture(_backgroundTexture);
	_quitGame.setString("Quit Game");
	_mainMenu.setString("Main Menu");
}

RunState::~RunState()
{
}

void RunState::Load()
{
	game = new GameManager();
	game->Load();
	_currentState = RunningState::Play;
	_isPress = false;
}

void RunState::Update(float deltaTime)
{
	if (_currentState == RunningState::Play)
	{
		game->Update(deltaTime);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		_isPress = false;

	if (!_isPress && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		switch (_currentState)
		{
		case RunningState::Play:
			_currentState = RunningState::Pause;
			break;
		case RunningState::Pause:
			_currentState = RunningState::Play;
			break;
		default:
			break;
		}
		_isPress = true;
	}
}

void RunState::Render(sf::RenderTarget* target)
{
	target->draw(_background);
	drawText("Lives: " + std::to_string(game->getLives()), sf::Vector2f(50, 24), 24, target, font);
	drawText("Score: " + std::to_string(game->getScore()), sf::Vector2f(200, 24), 24, target, font);
	drawText("Level: " + std::to_string(game->getLevel() + 1), sf::Vector2f(350, 24), 24, target, font);
	game->Render(target);
	

	if (_currentState == RunningState::Pause)
	{
		drawText("Pausing", sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT), 24, target, font);
		_mainMenu.drawButton(target);
		_quitGame.drawButton(target);
	}
		
}

GameState RunState::UpdateState(float deltaTime)
{
	Update(deltaTime);
	if (game->isOver())
		return GameState::Gameover;
	if (_quitGame.isPressed())
		return GameState::Exit;
	if (_mainMenu.isPressed())
		return GameState::Menu;
	return GameState::Run;
}

GameState RunState::GetState()
{
	return GameState::Run;
}

void RunState::Unload()
{
	delete game;
	game = nullptr;
}

int RunState::getScore()
{
	return game->getScore();
}
