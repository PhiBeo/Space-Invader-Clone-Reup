#include "Ship.h"
#include "Global.h"
#include "Bullet.h"

#define SHIP_RESPAWN_TIME 3
#define EXPLOSION_FRAME_TIMER 0.1

Ship::Ship() :
	Entity(),
	Collidable(SHIP_WIDTH / 2),
	_bullet(nullptr),
	_position(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_OFFSET)),
	_speed(200.f),
	_ship(),
	_lives(3),
	_getShoot(false),
	_respawnTime(SHIP_RESPAWN_TIME),
	_score(0),
	_isAlive(true),
	_playAnimationTimer(EXPLOSION_FRAME_TIMER),
	_currentFrame(0.f)
{
	if (!_shipTexture.loadFromFile(SHIP_TEXTURE))
		std::cout << "fail to load: SHIP_TEXTURE";
	_ship.setTexture(_shipTexture);
	_ship.setPosition(_position);
	_ship.setOrigin(_shipTexture.getSize().x / 2, _shipTexture.getSize().y / 2);

	if (!_explosionText.loadFromFile(EXPLOSION_TEXTURE))
		std::cout << "fail to load: EXPLOSION_TEXTURE" << std::endl;
	_explosion.setTexture(_explosionText);
	_explosion.setOrigin(_explosionText.getSize().x / 20, _explosionText.getSize().y / 2);
	_explosion.setPosition(_position);
	_explosion.setTextureRect(sf::IntRect(_currentFrame, 0, 40, 40));

	sound = Sound::getInstance();
}

Ship::~Ship()
{
}

void Ship::Load()
{
	_position = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_OFFSET);
	setCollisionFilter((int)EntityType::Enemy | (int)EntityType::Bullet_Enemy);
	_lives = 3;
	_getShoot = false;
	_respawnTime = SHIP_RESPAWN_TIME;
	_score = 0;
	_playAnimationTimer = EXPLOSION_FRAME_TIMER;
	_currentFrame = 0.f;
}

void Ship::Update(float deltaTime)
{
	UpdatePosition(deltaTime);
	shootBullet();
}

void Ship::Render(sf::RenderTarget* target)
{
	if (!_getShoot)
	{
		_ship.setPosition(_position);
		target->draw(_ship);
	}
	else if (_getShoot)
	{
		_explosion.setPosition(_position);
		target->draw(_explosion);
	}
}

void Ship::Unload()
{
}

const sf::Vector2f& Ship::getPosition() const
{
	return _position;
}

int Ship::getType() const
{
	return (int) EntityType::Player;
}

void Ship::onCollision(Collidable* collidable)
{
	if (_lives > 0)
	{
		_getShoot = true;
		_lives--;
		setCollisionFilter(0);
		sound->playerDie();
	}
}

void Ship::UpdatePosition(float deltaTime)
{
	if (!_getShoot && isAlive())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && _position.x >= SHIP_WIDTH / 2)
		{
			_position.x -= _speed * deltaTime;
			if (_position.x < SHIP_WIDTH / 2)
				_position.x = SHIP_WIDTH / 2;


		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && _position.x <= SCREEN_WIDTH - SHIP_WIDTH / 2)
		{
			_position.x += _speed * deltaTime;
			if (_position.x > SCREEN_WIDTH - SHIP_WIDTH / 2)
				_position.x = SCREEN_WIDTH - SHIP_WIDTH / 2;
		}
	}
	else if (_getShoot && isAlive())
	{
		_respawnTime -= deltaTime;
		if (_respawnTime <= 0)
		{
			_currentFrame = 0;
			respawn();
		}
		else
		{
			explosionAnimation(deltaTime);
		}
	}
}

bool Ship::isAlive()
{
	return _lives > 0;
}

void Ship::respawn()
{
	setCollisionFilter((int)EntityType::Enemy | (int)EntityType::Bullet_Enemy);
	_getShoot = false;
	_respawnTime = SHIP_RESPAWN_TIME;
	_position = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_OFFSET);
}

void Ship::addScore(int score)
{
	_score += score;
}

int Ship::getScore()
{
	return _score;
}

int Ship::getLives()
{
	return _lives;
}

void Ship::setBullet(Bullet* bullet)
{
	_bullet = bullet;
}

void Ship::shootBullet()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !_getShoot)
	{
		if (!_bullet->isActive())
		{
			sound->shooting();
		}
		_bullet->setActive(getPosition(), EntityType::Bullet_Player);	
	}
}

int Ship::getRespawnTime()
{
	return round(_respawnTime);
}

bool Ship::isShoot()
{
	return _getShoot;
}

void Ship::explosionAnimation(float deltaTime)
{
	_playAnimationTimer -= deltaTime;
	if (_playAnimationTimer <= 0)
	{
		_currentFrame += 40;
		_explosion.setTextureRect(sf::IntRect(_currentFrame, 0, 40, 40));
		if (_currentFrame >= 400)
			_currentFrame = 0;
		_playAnimationTimer = EXPLOSION_FRAME_TIMER;
	}
}

void Ship::setPosition(sf::Vector2f position)
{
	_position = position;
}
