#pragma once
#include "SFML/Graphics.hpp"
#include "Enums.h"

class Collidable
{
public:
	Collidable(float radius);
	virtual ~Collidable();

	virtual const sf::Vector2f& getPosition() const = 0;
	virtual int getType() const = 0;
	virtual void onCollision(Collidable* collidable) = 0;
	
	virtual float getRadius() const;
	virtual void setRadius(float radius);
	virtual bool didCollide(const Collidable* colliable) const;
	virtual void setCollisionFilter(int filter);
	virtual int getCollisionFilter() const;

private:
	float _radius;
	int _collisionFilter;
};

