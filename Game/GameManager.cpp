#include "GameManager.h"
#include "Global.h"
#include "DrawText.h"

#define LEVEL_UP_TIMER 3.f

GameManager::GameManager() :
	_ship(nullptr),
	_bullet(nullptr),
	_enemyBullet(nullptr),
	_enemiesPool(0),
	_level(0),
	_levelUpTime(LEVEL_UP_TIMER)
{
	if (!font.loadFromFile(GAME_FONT))
		std::cout << "fail to load: GAME_FONT" << std::endl;
}

void GameManager::Load()
{
	srand(time(NULL));

	_ship = new Ship;
	_ship->Load();
	addColliable(_ship);

	_bullet = new Bullet();
	_bullet->Load();
	_bullet->setSpeed(1000.f);
	addColliable(_bullet);
	_ship->setBullet(_bullet);

	_enemyBullet = new Bullet();
	_enemyBullet->Load();
	addColliable(_enemyBullet);

	_enemiesPool.Load();
	_enemiesPool.addCollision(collidables);
	_enemiesPool.addBullet(_enemyBullet);
	_enemiesPool.getPlayerHeight(_ship->getPosition().y);
	_enemiesPool.setShip(_ship);

	_level = 0;
	_levelUpTime = 3.f;
}

void GameManager::Update(float deltaTime)
{
	_ship->Update(deltaTime);
	_bullet->Update(deltaTime);
	_enemyBullet->Update(deltaTime);
	_enemiesPool.Update(deltaTime);

	auto numofColliable = collidables.size();
	for(int i = 0; i < numofColliable; i++)
		for (int j = i + 1; j < numofColliable; j++)
		{
			if (collidables[i]->didCollide(collidables[j]))
			{
				collidables[i]->onCollision(collidables[j]);
				collidables[j]->onCollision(collidables[i]);
			}
		}

	if (_enemiesPool.isAllDie())
	{
		_levelUpTime -= deltaTime;
		if (_levelUpTime <= 0)
		{
			_level++;
			_enemiesPool.levelUp(_level);
			_levelUpTime = LEVEL_UP_TIMER;
		}
	}
}

void GameManager::Render(sf::RenderTarget* target)
{
	_bullet->Render(target);
	_ship->Render(target);
	_enemyBullet->Render(target);
	_enemiesPool.Render(target);

	if (_enemiesPool.isAllDie())
	{
		drawText("Next Wave: " + std::to_string((int)_levelUpTime), sf::Vector2f(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT), 30, target, font);
	}
	else if (_ship->isShoot())
	{
		drawText("Ship respawn in: " + std::to_string(_ship->getRespawnTime()), sf::Vector2f(HALF_SCREEN_WIDTH, SCREEN_HEIGHT - SCREEN_OFFSET * 2), 30, target, font);
	}
}
	
void GameManager::Unload()
{
	_ship->Unload();
	_bullet->Unload();
	_enemiesPool.Unload();

	delete _ship;
	_ship = nullptr;
	delete _bullet;
	_bullet = nullptr;
	delete _enemyBullet;
	_enemyBullet = nullptr;
}

void GameManager::addColliable(Collidable* collide)
{
	collidables.push_back(collide);
}

bool GameManager::isOver()
{
	if (_ship->isAlive() == false || _enemiesPool.isReachGoal() == true)
		return true;
	return false;
}

int GameManager::getScore()
{
	return _ship->getScore();
}

int GameManager::getLives()
{
	return _ship->getLives();
}

int GameManager::getLevel()
{
	return _level;
}
