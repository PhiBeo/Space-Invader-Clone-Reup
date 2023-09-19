#pragma once
#include "SFML/Graphics.hpp"
#include "Ship.h"
#include "Bullet.h"
#include "EnemyPool.h"

class GameManager
{
public:
	GameManager();

	void Load();
	void Update(float deltaTime);
	void Render(sf::RenderTarget* target);
	void Unload();

	void addColliable(Collidable* collide);

	bool isOver();
	int getScore();
	int getLives();
	int getLevel();

private:
	sf::Font font;

	Ship* _ship;
	Bullet* _bullet;
	Bullet* _enemyBullet;
	EnemyPool _enemiesPool;
	std::vector<Collidable*> collidables;

	int _level;
	float _levelUpTime;
};

