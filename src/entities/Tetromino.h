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
			std::array<sf::Vertex, 16>		mVertices;
			std::vector<sf::FloatRect>		mRects;

			void						rotate();
			void						destroy();
			void						reachGround();
			sf::Vector2f			findCenter(const sf::VertexArray& shape);


			sf::Vector2f		getCenter() const;
			sf::FloatRect		getBoundingBox(std::vector<sf::FloatRect> rects) const;
			void				adjustBoundingBox();
			void				setCenter(sf::Vector2f& center);
			void				setGlobalRect(sf::FloatRect globalRect);
			bool				isTetrominoGrounded() const;
			//void				setCategory(Category::Type type);
			void				setShapeType(sf::PrimitiveType shapeType);
	
			virtual sf::FloatRect getBoundingRect() const;
		private:
			//virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
			std::vector<sf::FloatRect>constructRectListFromVertices(const sf::VertexArray& vertexArr);


		private:
			sf::Vector2f					mSize;
			sf::Vector2f					mCenter;
			sf::Color						mColor;
			sf::FloatRect					mGlobalRect;
			Type							mType;
			float							mAngle;
			bool							mIsGrounded;

};

#endif // !TETROMINO_H

