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
	explicit								Tetromino();
										Tetromino(Type type);
	sf::Transform					mRotation;
	sf::VertexArray					mShape;
	sf::Vector2f					mPosition;
	std::array<sf::Vertex, 8>		mVertices;

	void					rotate();
	void					destroy();
private:


private:
	sf::Vector2f		mSize;
	sf::Color			mColor;
	Type				mType;

};

#endif // !TETROMINO_H

