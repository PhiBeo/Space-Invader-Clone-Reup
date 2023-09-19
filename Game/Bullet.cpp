#include "Bullet.h"
#include "Global.h"

#define SWITCH_ANIMATION_TIMER .1f

Bullet::Bullet() :
	Entity(),
	Collidable(BULLET_WIDTH / 2),
	_position(0.f,0.f),
	_isActive(false),
	_speed(500.f),
	_direction(0),
	_type(),
	_switchAnimation(SWITCH_ANIMATION_TIMER),
	_currentFrame(0)
{
	if (!_bulletTexture.loadFromFile(BULLET_TEXTURE))
		std::cout << "fail to load: BULLET_TEXTURE";
	_bullet.setTexture(_bulletTexture);
	_bullet.setPosition(_position);
	_bullet.setTextureRect(sf::IntRect(_currentFrame, 0, BULLET_WIDTH, BULLET_HEIGHT));
	_bullet.setOrigin(_bulletTexture.getSize().x / 8, _bulletTexture.getSize().y / 2);
}

Bullet::~Bullet()
{
}

void Bullet::Load()
{
	_position = sf::Vector2f(0.f, 0.f);
	setCollisionFilter(0);
	_isActive = false;
	_direction = 0;
	_switchAnimation = .1f;
	_currentFrame = 0;
}

void Bullet::Update(float deltaTime)
{
	if (_isActive)
	{
		animation(deltaTime);
		_position.y += _direction * _speed * deltaTime;
		if (_position.y <= -BULLET_HEIGHT || _position.y >= SCREEN_HEIGHT + BULLET_HEIGHT)
		{
			_isActive = false;
		}
	}
}

void Bullet::Render(sf::RenderTarget* target)
{
	if (_isActive)
	{
		_bullet.setPosition(_position);
		target->draw(_bullet);
	}
}

void Bullet::Unload()
{
}

const sf::Vector2f& Bullet::getPosition() const
{
	return _position;
}

int Bullet::getType() const
{
	return (int) _type;
}

void Bullet::onCollision(Collidable* collidable)
{
	setCollisionFilter(0);
	_isActive = false;
}

void Bullet::setActive(sf::Vector2f position, EntityType type)
{
	if (!_isActive)
	{
		_isActive = true;
		_position = position;
		_type = type;

		if (_type == EntityType::Bullet_Enemy)
		{
			_direction = 1;
			setCollisionFilter((int)EntityType::Player | (int)EntityType::Bullet_Player);
			_bullet.setRotation(180);
		}
		else if (_type == EntityType::Bullet_Player)
		{
			_direction = -1;
			setCollisionFilter((int)EntityType::Enemy | (int)EntityType::Bullet_Enemy);
		}
	}
}

bool Bullet::isActive()
{
	return _isActive;
}

void Bullet::setSpeed(float speed)
{
	_speed = speed;
}

void Bullet::animation(float deltaTime)
{
	_switchAnimation -= deltaTime;
	if (_switchAnimation <= 0)
	{
		_currentFrame += BULLET_WIDTH;
		_bullet.setTextureRect(sf::IntRect(_currentFrame, 0, BULLET_WIDTH, BULLET_HEIGHT));
		if (_currentFrame >= BULLET_WIDTH * 3)
			_currentFrame = 0;
		_switchAnimation = SWITCH_ANIMATION_TIMER;
	}

}
