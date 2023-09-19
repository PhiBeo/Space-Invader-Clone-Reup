#pragma once
#include "Entity.h"
#include "Collidable.h"
#include "SFML/Graphics.hpp"
#include "Sound.h"

class Bullet;

class Ship : public Entity, public Collidable
{
public:
	Ship();
	virtual ~Ship();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	void Unload() override;

	const sf::Vector2f& getPosition() const;
	int getType() const;
	void onCollision(Collidable* collidable);

	void setPosition(sf::Vector2f position);

	void UpdatePosition(float deltaTime);
	bool isAlive();
	void respawn();
	void addScore(int score);
	int getScore();
	int getLives();
	void setBullet(Bullet* bullet);
	void shootBullet();

	int getRespawnTime();
	bool isShoot();
	void explosionAnimation(float deltaTime);


private:
	sf::Vector2f _position;
	float _speed;
	int _lives;
	bool _getShoot;
	bool _isAlive;

	float _respawnTime;
	int _score;
	Bullet* _bullet;

	sf::Texture _shipTexture;
	sf::Sprite _ship;

	sf::Texture _explosionText;
	sf::Sprite _explosion;
	float _playAnimationTimer;
	float _currentFrame;

	Sound* sound;
};

