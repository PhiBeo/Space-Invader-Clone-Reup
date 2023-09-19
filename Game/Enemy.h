#pragma once
#include "Entity.h"
#include "Collidable.h"
#include "SFML/Graphics.hpp"
#include "Sound.h"

class Ship;

enum class Direction
{
	Down,
	Left,
	Right,
};

class Enemy : public Entity, public Collidable
{
public:
	Enemy(short int id);
	virtual ~Enemy();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	void Unload() override;

	const sf::Vector2f& getPosition() const;
	int getType() const;
	void onCollision(Collidable* collidable);

	void setDirection(Direction direction);
	void setPosition(sf::Vector2f position);
	void setSpeed(float speed);
	void setShip(Ship* ship);

	bool isWallCollide();
	bool finishMoveDown();
	bool isAlive();

	void Animation(float deltaTime);
	void ExplosionAnimation(float deltaTime);

private:
	sf::Vector2f _position;
	bool _isAlive;
	short int _id;
	float _speed;


	float _lastHeight;
	
	Direction _currentDirection;

	Ship* _ship;

	sf::Texture _enemyTexture;
	sf::Sprite _enemy;
	float _currentFrame;
	float _switchTime;

	sf::Texture _explosionText;
	sf::Sprite _explosion;

	float _animationTimer;
	float _animationDuration;
	float _explosionCurrentFrame;

	Sound* sound;
};

