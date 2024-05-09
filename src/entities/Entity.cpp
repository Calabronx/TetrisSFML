#include "Entity.h"
#include <regex>
#include <iostream>

Entity::Entity()
	: mVelocity()
	, mLifes(1)
	, mIsLanded(false)
{
}

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

void Entity::destroy()
{
	//mIsInactive = true;
	mLifes = 0;
}

void Entity::land()
{
	mIsLanded = true;
}

bool Entity::isDestroyed() const
{
	return mLifes <= 0 ? true : false;
}

bool Entity::isLanded() const
{
	return mIsLanded;
}

void Entity::updateCurrent(sf::Time dt)
{
	if (!mIsLanded)
		move(mVelocity * dt.asSeconds());
}
