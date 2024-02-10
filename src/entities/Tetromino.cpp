#include "Tetromino.h"

Tetromino::Tetromino()
{
}

Tetromino::Tetromino(std::array<sf::Vertex, 8> vertices)
	: mShape(sf::TriangleFan)
	, mVertices(vertices)
{
	for (auto i = 0; i < mVertices.size(); i++) {
		mShape.append(mVertices[i]);
	}
}

void Tetromino::rotate()
{
}

void Tetromino::destroy()
{
}
