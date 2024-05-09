#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "../nodes/SceneNode.h"

class Entity : public SceneNode
{
		public:
			explicit						Entity();
			void							setVelocity(sf::Vector2f velocity);
			void							setVelocity(float vx, float vy);
			void							moveEntity(sf::Vector2f velocity);
			void							moveEntity(float vx,float vy);
			sf::Vector2f				getVelocity() const;
			void						destroy();
			void						land();
			virtual bool	isDestroyed() const;
			bool	isLanded() const;
			virtual void updateCurrent(sf::Time dt);

		private:

		private:
			sf::Vector2f		mVelocity;
			bool					mIsLanded;
			int							mLifes;
};
#endif // !ENTITY_H

 