#include "Collidable.h"

Collidable::Collidable(float radius) :
	_radius(radius),
	_collisionFilter(-1)
{
}

Collidable::~Collidable()
{
}

bool Collidable::didCollide(const Collidable* colliable) const
{
	bool didCollide = false;
	if (colliable != nullptr)
	{
		int colliableFilter = colliable->getCollisionFilter();
		int collisionFilter = getCollisionFilter();
		if (colliableFilter != 0 && collisionFilter != 0)
		{
			if (colliableFilter < 0 || collisionFilter < 0 || (colliableFilter & getType()) > 0)
			{
				float distanceSqr = pow(pow(colliable->getPosition().x - getPosition().x, 2) + pow(colliable->getPosition().y - getPosition().y, 2), 0.5f);
				float radiusSqr = colliable->getRadius() + getRadius();//sqrtf(colliable->getRadius() + getRadius());

				didCollide = distanceSqr <= radiusSqr;
			}
		}
	}
	return didCollide;
}

float Collidable::getRadius() const
{
	return _radius;
}

void Collidable::setRadius(float radius)
{
	_radius = radius;
}

void Collidable::setCollisionFilter(int filter)
{
	_collisionFilter = filter;
}

int Collidable::getCollisionFilter() const
{
	return _collisionFilter;
}
