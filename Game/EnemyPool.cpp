#include "EnemyPool.h"
#include "Global.h"
#include "Bullet.h"

#define ROW 5
#define COLUMN 11
#define GAP_INCREASE 100

EnemyPool::EnemyPool(Bullet* bullet) :
	_wasRight(true),
	_currentDirection(Direction::Right),
	_bullet(bullet),
	_isAllDie(false),
	_level(0)
{
	int id = 2;

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			Enemy* newEnemy = new Enemy(id);
			newEnemy->setPosition(sf::Vector2f(50 + ENEMY_GAP_WIDTH * j, 80 + ENEMY_GAP_HEIGHT * i));

			_enemies.push_back(newEnemy);
		}

		if (i == 0)
			id--;
		else if (i == 2)
			id--;
	}
}

EnemyPool::~EnemyPool()
{
}

void EnemyPool::Load()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->Load();
	}

	_isAllDie = false;
	_wasRight = true;
	_currentDirection = Direction::Right;
	_level = 0;
}

void EnemyPool::Update(float deltaTime)
{
	directionUpdate();

	std::vector<Enemy*> aliveEnemy;
	for (int i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->isAlive())
		{
			aliveEnemy.push_back(_enemies[i]);
		}
	}

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->Update(deltaTime);
	}

	if (!_bullet->isActive())
	{
		if (aliveEnemy.size() > 0)
		{
			int shootEnemy = rand() % aliveEnemy.size();

			_bullet->setActive(sf::Vector2f(aliveEnemy[shootEnemy]->getPosition().x, aliveEnemy[shootEnemy]->getPosition().y), EntityType::Bullet_Enemy);
		}
	}

	if (aliveEnemy.size() == 23)
		setSpeed(100);
	else if (aliveEnemy.size() == 10)
		setSpeed(150);
	else if (aliveEnemy.size() == 1)
		setSpeed(400);
	else if (aliveEnemy.size() == 0)
		_isAllDie = true;

	aliveEnemy.clear();
}

void EnemyPool::Render(sf::RenderTarget* target)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->Render(target);
	}
}

void EnemyPool::Unload()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i] != nullptr)
		{
			delete _enemies[i];
			_enemies[i] = nullptr;
		}
	}

	_enemies.clear();
}

void EnemyPool::checkDirection()
{
	if (_currentDirection == Direction::Left)
	{
		_wasRight = false;
	}
	else if (_currentDirection == Direction::Right)
	{
		_wasRight = true;
	}
}

void EnemyPool::addCollision(std::vector<Collidable*>& colliable)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		colliable.push_back(_enemies[i]);
	}
}

void EnemyPool::addBullet(Bullet* bullet)
{
	_bullet = bullet;
}

void EnemyPool::setDirection()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->setDirection(_currentDirection);
	}
}

void EnemyPool::setSpeed(float speed)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->setSpeed(speed);
	}
}

bool EnemyPool::isAllDie()
{
	return _isAllDie;
}

void EnemyPool::levelUp(int level)
{
	if (level < 5)
		_level = level;

	std::vector<sf::Vector2f> position;

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			position.push_back(sf::Vector2f(sf::Vector2f(50 + ENEMY_GAP_WIDTH * j, (80 + ENEMY_GAP_HEIGHT * i) + GAP_INCREASE * _level)));
		}
	}

	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->setPosition(position[i]);
		_enemies[i]->Load();
	}

	_isAllDie = false;
	position.clear();
}

void EnemyPool::getPlayerHeight(float height)
{
	_goal = height - (SHIP_HEIGHT * 2);
}

bool EnemyPool::isReachGoal()
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->getPosition().y - ENEMY_RED_HEIGHT / 2 >= _goal)
		{
			return true;
		}
	}
	return false;
}

void EnemyPool::setShip(Ship* ship)
{
	for (int i = 0; i < _enemies.size(); i++)
	{
		_enemies[i]->setShip(ship);
	}
}

void EnemyPool::directionUpdate()
{
	checkDirection();

	for (int i = 0; i < _enemies.size(); i++)
	{
		if (_enemies[i]->isWallCollide())
		{
			if (_enemies[i]->isAlive())
			{
				_currentDirection = Direction::Down;
			}
		}
	}

	if (_currentDirection == Direction::Down)
	{
		for (int i = 0; i < _enemies.size(); i++)
		{
			if (_enemies[i]->finishMoveDown())
			{
				switch (_wasRight)
				{
				case true:
					_currentDirection = Direction::Left;
					break;
				case false:
					_currentDirection = Direction::Right;
					break;
				default:
					break;
				}
				break;
			}
		}
	}

	setDirection();
}
