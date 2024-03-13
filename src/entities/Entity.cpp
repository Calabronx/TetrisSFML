#include "Entity.h"
#include <iostream>

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

void Entity::moveEntity(sf::Vector2f velocity)
{
	// tratar de implementar otra manera de castear los limites de velocidad..
	if (mVelocity.y > 10 || mVelocity.y < 0)
		mVelocity.y = 0;
	
	if (mVelocity.x > 10 || mVelocity.x < 0)
		mVelocity.x = 0;

	mVelocity += velocity;

	std::cout << mVelocity.y << std::endl;
}

void Entity::moveEntity(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}


sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::setTransform(sf::Transform transform)
{
	mTransform = transform;
}
sf::Transform Entity::getTransform() const
{
	return mTransform;
}

void Entity::updateCurrent(sf::Time dt)
{
	move(mVelocity * dt.asSeconds());
}
