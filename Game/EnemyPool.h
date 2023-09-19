#pragma once
#include "Enemy.h"

#include <vector>

class Bullet;

class EnemyPool
{
public:
	EnemyPool(Bullet* bullet);
	virtual ~EnemyPool();
	
	void Load();
	void Update(float deltaTime);
	void Render(sf::RenderTarget* target);
	void Unload();

	void checkDirection();
	void addCollision(std::vector<Collidable*>& colliable);
	void addBullet(Bullet* bullet);
	void directionUpdate();
	void setDirection();
	void setSpeed(float speed);
	bool isAllDie();
	void levelUp(int level);
	void getPlayerHeight(float height);
	bool isReachGoal();
	void setShip(Ship* ship);

private:
	std::vector<Enemy*> _enemies;
	Bullet* _bullet;

	Direction _currentDirection;
	bool _wasRight;
	bool _isAllDie;
	int _level;
	float _goal;
};

