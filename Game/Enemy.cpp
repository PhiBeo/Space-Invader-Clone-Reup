#include "Enemy.h"
#include "Global.h"
#include "Ship.h"

#define SPEED 80.f
#define SWITCH_TIME .1f
#define ANIMATION_DURATION 1

Enemy::Enemy(short int id) :
	Entity(),
	Collidable(0.f),
	_ship(nullptr),
	_position(0.f,0.f),
	_isAlive(true),
	_id(id),
	_speed(SPEED),
	_currentDirection(Direction::Right),
	_lastHeight(0.f),
	_currentFrame(0),
	_switchTime(SWITCH_TIME),
	_animationDuration(ANIMATION_DURATION),
	_explosionCurrentFrame(0.f),
	_animationTimer(SWITCH_TIME)
{
	switch (_id)
	{
	case 0:
		_enemyTexture.loadFromFile(RED_ENEMY_TEXTURE);
		_enemy.setTexture(_enemyTexture);
		setRadius(ENEMY_RED_HEIGHT / 2);
		_enemy.setTextureRect(sf::IntRect(_currentFrame, 0, ENEMY_RED_WIDTH, ENEMY_RED_HEIGHT));
		break;
	case 1:
		_enemyTexture.loadFromFile(BLUE_ENEMY_TEXTURE);
		_enemy.setTexture(_enemyTexture);
		setRadius(ENEMY_BLUE_HEIGHT / 2);
		_enemy.setTextureRect(sf::IntRect(_currentFrame, 0, ENEMY_BLUE_WIDTH, ENEMY_BLUE_HEIGHT));
		break;
	case 2:
		_enemyTexture.loadFromFile(GREEN_ENEMY_TEXTURE);
		_enemy.setTexture(_enemyTexture);
		setRadius(ENEMY_GREEN_HEIGHT / 2);
		_enemy.setTextureRect(sf::IntRect(_currentFrame, 0, ENEMY_GREEN_WIDTH, ENEMY_GREEN_HEIGHT));
		break;
	default:
		break;
	}
	_enemy.setOrigin(_enemyTexture.getSize().x / 8, _enemyTexture.getSize().y / 2);


	if (!_explosionText.loadFromFile(EXPLOSION_TEXTURE))
		std::cout << "fail to load: EXPLOSION_TEXTURE" << std::endl;
	_explosion.setTexture(_explosionText);
	_explosion.setOrigin(_explosionText.getSize().x / 20, _explosionText.getSize().y / 2);
	_explosion.setPosition(_position);
	_explosion.setTextureRect(sf::IntRect(_currentFrame, 0, 40, 40));

	sound = Sound::getInstance();
}

Enemy::~Enemy()
{
}

void Enemy::Load()
{
	setCollisionFilter((int)EntityType::Bullet_Player | (int)EntityType::Player);
	_enemy.setPosition(_position);
	_currentDirection = Direction::Right;
	_speed = SPEED;
	_lastHeight = 0.f;
	_isAlive = true;
	_switchTime = SWITCH_TIME;
	_animationDuration = ANIMATION_DURATION;
	_animationTimer = SWITCH_TIME;
	_explosionCurrentFrame = 0.f;
}

void Enemy::Update(float deltaTime)
{
	if (_isAlive)
	{
		switch (_currentDirection)
		{
		case Direction::Down:
			_position.y += _speed * deltaTime;
			break;
		case Direction::Left:
			_position.x -= _speed * deltaTime;
			break;
		case Direction::Right:
			_position.x += _speed * deltaTime;
			break;
		default:
			break;
		}
		if (_currentDirection != Direction::Down)
		{
			_lastHeight = _position.y;
		}

		Animation(deltaTime);
	}
	else
	{
		if (_animationDuration >= 0)
		{
			ExplosionAnimation(deltaTime);
		}
	}
}

void Enemy::Render(sf::RenderTarget* target)
{
	if (_isAlive)
	{
		_enemy.setPosition(_position);
		target->draw(_enemy);
	}
	else if (!_isAlive && _animationDuration >= 0)
	{
		_explosion.setPosition(_position);
		target->draw(_explosion);
	}
}

void Enemy::Unload()
{
}

const sf::Vector2f& Enemy::getPosition() const
{
	return _position;
}

int Enemy::getType() const
{
	return (int) EntityType::Enemy;
}

void Enemy::onCollision(Collidable* collidable)
{
	_isAlive = false;
	setCollisionFilter(0);
	sound->enemyDie();

	switch (_id)
	{
	case 0:
		_ship->addScore(100);
		break;
	case 1:
		_ship->addScore(200);
		break;
	case 2:
		_ship->addScore(300);
		break;
	default:
		break;
	}
}

void Enemy::setDirection(Direction direction)
{
	_currentDirection = direction;
}

void Enemy::setPosition(sf::Vector2f position)
{
	_position = position;
}

void Enemy::setSpeed(float speed)
{
	_speed = speed;
}

void Enemy::setShip(Ship* ship)
{
	_ship = ship;
}

bool Enemy::isWallCollide()
{
	if (_position.x - ENEMY_RED_WIDTH / 2 <= 0 || _position.x + ENEMY_RED_WIDTH / 2 >= SCREEN_WIDTH)
	{
		if (_position.x - ENEMY_RED_WIDTH / 2 <= 0)
		{
			_position.x = ENEMY_RED_WIDTH / 2 + 2;
		}
		else
		{
			_position.x = SCREEN_WIDTH - (ENEMY_RED_WIDTH / 2 + 2);
		}
		return true;
	}
	return false;
}

bool Enemy::finishMoveDown()
{
	if (_currentDirection == Direction::Down)
	{
		if (_position.y >= _lastHeight + MOVE_DOWN_DISTANCE)
		{
			return true;
		}
	}
	return false;
}

bool Enemy::isAlive()
{
	return _isAlive;
}

void Enemy::Animation(float deltaTime)
{
	_switchTime -= deltaTime;
	float frameWidth;
	float frameHeight;
	switch (_id)
	{
	case 0:
		frameWidth = ENEMY_RED_WIDTH;
		frameHeight = ENEMY_RED_HEIGHT;
		break;
	case 1:
		frameWidth = ENEMY_BLUE_WIDTH;
		frameHeight = ENEMY_BLUE_HEIGHT;
		break;
	case 2:
		frameWidth = ENEMY_GREEN_WIDTH;
		frameHeight = ENEMY_BLUE_HEIGHT;
		break;
	default:
		break;
	}

	if (_switchTime <= 0)
	{
		_currentFrame += frameWidth;
		_enemy.setTextureRect(sf::IntRect(_currentFrame, 0, frameWidth, frameHeight));
		if (_currentFrame >= frameWidth * 3)
			_currentFrame = 0;
		_switchTime = SWITCH_TIME;
	}
	
}

void Enemy::ExplosionAnimation(float deltaTime)
{
	_animationDuration -= deltaTime;
	_animationTimer -= deltaTime;
	if (_animationTimer <= 0)
	{
		_explosionCurrentFrame += 40;
		_explosion.setTextureRect(sf::IntRect(_explosionCurrentFrame, 0, 40, 40));
		if (_explosionCurrentFrame >= 400)
		{
			_explosionCurrentFrame = 0;
		}
		_animationTimer = SWITCH_TIME;
	}
}
