#include "IntructionState.h"
#include "Global.h"
#include "DrawText.h"

IntructionState::IntructionState(sf::RenderWindow* window) :
	State(window, GameState::Intruction),
	_return(window, sf::Vector2f(SCREEN_WIDTH - BUTTON_WIDTH / 1.5, SCREEN_HEIGHT - BUTTON_HEIGHT))
{
	if (!font.loadFromFile(DEFAULT_FONT))
		std::cout << "Fail to load: DEFAULT_FONT" << std::endl;
	if (!_redEnemyText.loadFromFile(RED_ENEMY_TEXTURE))
		std::cout << "fail to load: RED_ENEMY_TEXTURE" << std::endl;
	if (!_blueEnemyText.loadFromFile(BLUE_ENEMY_TEXTURE))
		std::cout << "fail to load: RED_ENEMY_TEXTURE" << std::endl;
	if (!_greenEnemyText.loadFromFile(GREEN_ENEMY_TEXTURE))
		std::cout << "fail to load: RED_ENEMY_TEXTURE" << std::endl;

	_redEnemy.setTexture(_redEnemyText);
	_blueEnemy.setTexture(_blueEnemyText);
	_greenEnemy.setTexture(_greenEnemyText);

	_redEnemy.setOrigin(_redEnemyText.getSize().x / 8, _redEnemyText.getSize().y / 2);
	_blueEnemy.setOrigin(_blueEnemyText.getSize().x / 8, _blueEnemyText.getSize().y / 2);
	_greenEnemy.setOrigin(_greenEnemyText.getSize().x / 8, _greenEnemyText.getSize().y / 2);

	_redEnemy.setTextureRect(sf::IntRect(0, 0, ENEMY_RED_WIDTH, ENEMY_RED_HEIGHT));
	_blueEnemy.setTextureRect(sf::IntRect(0, 0, ENEMY_BLUE_WIDTH, ENEMY_BLUE_HEIGHT));
	_greenEnemy.setTextureRect(sf::IntRect(0, 0, ENEMY_GREEN_WIDTH, ENEMY_GREEN_HEIGHT));

	_redEnemy.setPosition(HALF_SCREEN_WIDTH - ENEMY_GAP_WIDTH, HALF_SCREEN_HEIGHT);
	_blueEnemy.setPosition(HALF_SCREEN_WIDTH - ENEMY_GAP_WIDTH, HALF_SCREEN_HEIGHT + ENEMY_GAP_HEIGHT);
	_greenEnemy.setPosition(HALF_SCREEN_WIDTH - ENEMY_GAP_WIDTH, HALF_SCREEN_HEIGHT + ENEMY_GAP_HEIGHT * 2);

}

IntructionState::~IntructionState()
{
}

void IntructionState::Load()
{
	_return.setString("Back");


}

void IntructionState::Update(float deltaTime)
{
}

void IntructionState::Render(sf::RenderTarget* target)
{
	drawText("How to play", sf::Vector2f(HALF_SCREEN_WIDTH, SCREEN_OFFSET / 2), 30, target, font);
	drawText("A & D keys to move the ship", sf::Vector2f(HALF_SCREEN_WIDTH, (SCREEN_OFFSET / 2) * 2), 24, target, font);
	drawText("Space key to shoot", sf::Vector2f(HALF_SCREEN_WIDTH, (SCREEN_OFFSET / 2) * 3), 24, target, font);
	drawText("Your objective is to destroy all the UFO and survive through the waves", sf::Vector2f(HALF_SCREEN_WIDTH, (SCREEN_OFFSET / 2) * 4), 24, target, font);
	drawText("You will have 3 chance", sf::Vector2f(HALF_SCREEN_WIDTH, (SCREEN_OFFSET / 2) * 5), 24, target, font);
	drawText("Points:", sf::Vector2f(HALF_SCREEN_WIDTH, (SCREEN_OFFSET / 2) * 6), 24, target, font);

	target->draw(_redEnemy);
	drawText("100", sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT), 24, target, font);
	target->draw(_blueEnemy);
	drawText("200", sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + ENEMY_GAP_HEIGHT), 24, target, font);
	target->draw(_greenEnemy);
	drawText("300", sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT + ENEMY_GAP_HEIGHT * 2), 24, target, font);


	_return.drawButton(target);
}

GameState IntructionState::UpdateState(float deltaTime)
{
	Update(deltaTime);
	if (_return.isPressed())
		return GameState::Menu;

	return GameState::Intruction;
}

GameState IntructionState::GetState()
{
	return GameState::Intruction;
}

void IntructionState::Unload()
{
}

