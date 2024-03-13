#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "../nodes/SceneNode.h"

class Entity : public SceneNode
{
		public:
			void							setVelocity(sf::Vector2f velocity);
			void							setVelocity(float vx, float vy);
			void							moveEntity(sf::Vector2f velocity);
			void							moveEntity(float vx,float vy);
			void							setTransform(sf::Transform transform);
			sf::Vector2f				getVelocity() const;
			sf::Transform				getTransform() const;

		private:
			virtual void updateCurrent(sf::Time dt);

		public:
			sf::Transform		mTransform;

		private:
			sf::Vector2f		mVelocity;
};
#endif // !ENTITY_H

 