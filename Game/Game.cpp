#include "Game.h"
#include "Global.h"
#include "DrawText.h"

Game::Game() :
	_window(new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_NAME)),
	ev(),
	_menuState(_window),
	_gameoverState(_window),
	_instructionState(_window),
	_settingState(_window),
	_runState(_window),
	_splashScreenState(_window),
	currentState(GameState::Entry),
	deltaTime(0.f),
	dtClock()
{
	if (!font.loadFromFile(DEFAULT_FONT))
		throw("Fail to load: DEFAULT_FONT");
}

Game::~Game()
{
}

void Game::GameInit()
{
	Load();
}

void Game::GameRunning()
{
	while (_window->isOpen())
	{
		WindowPollEv();

		UpdateDeltaTime();

		Update();

		Render();
	}
	
}

void Game::GameShutDown()
{
	_menuState.Unload();
	_gameoverState.Unload();
	_instructionState.Unload();
	_runState.Unload();

	delete _window;
}

void Game::Load()
{
	switch (currentState)
	{
	case GameState::Menu:
		_menuState.Load();
		break;
	case GameState::Intruction:
		_instructionState.Load();
		break;
	case GameState::Settting:
		_settingState.Load();
		break;
	case GameState::Run:
		_runState.Load();
		break;
	case GameState::Gameover:
		_gameoverState.Load();
		break;
	case GameState::Exit:
		_window->close();
		break;
	case GameState::Entry:
		_splashScreenState.Load();
		break;
	default:
		break;
	}
}

void Game::Update()
{

	GameState thisState = currentState;

	switch (currentState)
	{
	case GameState::Menu:
		currentState = _menuState.UpdateState(deltaTime);
		break;
	case GameState::Intruction:
		currentState = _instructionState.UpdateState(deltaTime);
		break;
	case GameState::Settting:
		currentState = _settingState.UpdateState(deltaTime);
		break;
	case GameState::Run:
		currentState = _runState.UpdateState(deltaTime);
		break;
	case GameState::Gameover:
		currentState = _gameoverState.UpdateState(deltaTime);
		break;
	case GameState::Entry:
		currentState = _splashScreenState.UpdateState(deltaTime);
		break;
	default:
		break;
	}
	
	if (thisState != currentState)
	{
		switch (thisState)
		{
		case GameState::Menu:
			_menuState.Unload();
			break;
		case GameState::Intruction:
			_instructionState.Unload();
			break;
		case GameState::Settting:
			_settingState.Unload();
			break;
		case GameState::Run:
			_gameoverState.setScore(_runState.getScore());
			_runState.Unload();
			break;
		case GameState::Gameover:
			_gameoverState.Unload();
			break;
		default:
			break;
		}
		Load();
	}
}

void Game::Render()
{
	_window->clear(sf::Color(128, 128, 128));

	switch (currentState)
	{
	case GameState::Menu:
		_menuState.Render(_window);
		break;
	case GameState::Intruction:
		_instructionState.Render(_window);
		break;
	case GameState::Settting:
		_settingState.Render(_window);
		break;
	case GameState::Run:
		_runState.Render(_window);
		break;
	case GameState::Gameover:
		_gameoverState.Render(_window);
		break;
	case GameState::Entry:
		_splashScreenState.Render(_window);
		break;
	default:
		break;
	}

	_window->display();
}

void Game::UpdateDeltaTime()
{
	deltaTime = dtClock.restart().asSeconds();
}

void Game::WindowPollEv()
{
	while (_window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			_window->close();
			break;
		default:
			break;
		}
	}
}


