#pragma once
#ifndef TETROMINO_H
#define TETROMINO_H

#include "Entity.h"
#include <array>

class Tetromino : public Entity
{

public:

	enum TetrominoID {
		T,
		L,
		J,
		O,
		S,
		Z
	};

	struct TetrominoStruct {
		std::array<sf::Vertex, 8> vertices;
		sf::Color color;
	};

public:
	explicit								Tetromino();
										Tetromino(std::array<sf::Vertex, 8> vertices);
	sf::VertexArray					mShape;
	sf::Vector2f					mPosition;
	std::array<sf::Vertex, 8>		mVertices;

private:

	void					rotate();
	void					destroy();

private:
	sf::Vector2f		mSize;
	sf::Color			mColor;

};

#endif // !TETROMINO_H

