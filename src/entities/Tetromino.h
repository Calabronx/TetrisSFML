#pragma once
#ifndef TETROMINO_H
#define TETROMINO_H

#include "Entity.h"
#include <array>
#include "../input/CommandQueue.h"

class Tetromino : public Entity
{

		public:

			enum Type
			{
					L,
					T,
					J,
					O,
					S,
					Z
			};

		public:
			virtual unsigned int getCategory() const;

		public:
			explicit									Tetromino(Type type);
			virtual void								drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
			sf::Transform					mRotation;
			sf::VertexArray					mShape;
			std::array<sf::Vertex, 8>		mVertices;

			void						rotate();
			void						destroy();
			void						reachGround();
			sf::Vector2f			findCenter(const sf::VertexArray& shape);


			sf::Vector2f		getCenter() const;
			void				setCenter(sf::Vector2f& center);
			bool				isTetrominoGrounded() const;
			void				setCategory(Category::Type type);
	
			virtual sf::FloatRect getBoundingRect() const;
		private:
			//virtual void updateCurrent(sf::Time dt, CommandQueue& commands);


		private:
			sf::Vector2f					mSize;
			sf::Vector2f					mCenter;
			sf::Color						mColor;
			Type							mType;
			float							mAngle;
			bool							mIsGrounded;

};

#endif // !TETROMINO_H

