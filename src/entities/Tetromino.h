#pragma once
#ifndef TETROMINO_H
#define TETROMINO_H

#include "Entity.h"
#include <array>

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
			explicit									Tetromino(Type type);
			virtual void								drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
			sf::Transform					mRotation;
			sf::VertexArray					mShape;
			sf::Vector2f					mPosition;
			std::array<sf::Vertex, 8>		mVertices;

			void						rotate(sf::Transform& transform);
			void						destroy();
			sf::Vector2f			findCenter(const sf::VertexArray& shape);

			sf::Vector2f		getCenter() const;
			void				setCenter(sf::Vector2f& center);
		private:


		private:
			sf::Vector2f					mSize;
			sf::Vector2f					mCenter;
			sf::Color						mColor;
			Type							mType;

};

#endif // !TETROMINO_H

