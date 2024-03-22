#include "Entity.h"
#include <regex>
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

void Entity::moveEntity(float vx, float vy)
{
	//assert(vx != 0.f);
	
	mVelocity.x += vx;
	mVelocity.y += vy;
}

void Entity::moveEntity(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::updateCurrent(sf::Time dt)
{
	move(mVelocity * dt.asSeconds());
}
