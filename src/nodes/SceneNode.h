#pragma once
#ifndef SCENENODE_H
#define SCENENODE_H

#include<vector>

#include<SFML/Graphics.hpp>
#include "../util/Category.h"
#include "../input/Command.hpp"
#include <set>
//#include "../input/CommandQueue.h"

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
		public:
			typedef std::unique_ptr<SceneNode> Ptr;
			typedef std::pair<SceneNode*, SceneNode*> Pair;

		public:
													SceneNode();
			void						attachChild(Ptr child);
			Ptr									detachChild(const SceneNode& node);

			void						update(sf::Time dt);

			sf::Vector2f			getWorldPosition() const;
			sf::Transform			getWorldTransform() const;

			void											onCommand(const Command& command, sf::Time dt);


			virtual unsigned int	getCategory() const;

			void							checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
			void							checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);


			virtual sf::FloatRect	getBoundingRect() const;
			virtual bool isDestroyed() const;
			virtual bool isMarkedForRemoval() const;

		private:
			virtual void			updateCurrent(sf::Time dt);
			void						updateChildren(sf::Time dt);

			virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
			virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
			void						drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

		private:
			std::vector<Ptr>		mChildren;
			SceneNode*						mParent;
			
};

bool collision(const SceneNode& lhs, const SceneNode& rhs);
float distance(const SceneNode& lhs, const SceneNode& rhs);
#endif // !SCENENODE_H

