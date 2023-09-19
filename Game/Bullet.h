#pragma once
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include "Enums.h"
#include "Collidable.h"

class Bullet : public Entity, public Collidable
{
public:
	Bullet();
	virtual ~Bullet();

	void Load() override;
	void Update(float deltaTime) override;
	void Render(sf::RenderTarget* target) override;
	void Unload() override;

	const sf::Vector2f& getPosition() const;
	int getType() const;
	void onCollision(Collidable* collidable);

	void setActive(sf::Vector2f position, EntityType type);
	bool isActive();
	void setSpeed(float speed);

	void animation(float deltaTime);

private:
	sf::Vector2f _position;
	EntityType _type;
	float _speed;
	short int _direction;
	bool _isActive;

	float _switchAnimation;
	float _currentFrame;

	sf::Texture _bulletTexture;
	sf::Sprite _bullet;
};

