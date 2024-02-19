#include "Tetromino.h"
#include "../util/DataTables.h"
#include <iostream>

namespace {
	const std::vector<TetrominoData> TetrominoTable = initializeTetrominoData();
}

Tetromino::Tetromino(Type type)
	: mShape(sf::TriangleFan)
	, mType(type)
	, mRotation()
	, mVertices(TetrominoTable[type].vertices)
{
	for (auto i = 0; i < mVertices.size(); i++) {
		mShape.append(mVertices[i]);
		mCenter = findCenter(mShape);
	}
}

void Tetromino::rotate(sf::Transform& transform)
{
	mTransform = transform;
	std::cout << "rotating" << std::endl;
	//mTransform.rotate(20.f);
	//mTransform.transformPoint(mPosition);
	mRotation.rotate(25.0f);

	mTransform = mRotation;
}

void Tetromino::destroy()
{
}

sf::Vector2f Tetromino::findCenter(const sf::VertexArray& vertices) {
	sf::Vector2f sum(0.f, 0.f);
	for (std::size_t i = 0; i < vertices.getVertexCount(); ++i) {
		sum += vertices[i].position;
	}
	if (vertices.getVertexCount() > 0) {
		sum.x /= static_cast<float>(vertices.getVertexCount());
		sum.y /= static_cast<float>(vertices.getVertexCount());
	}
	return sum;
}

sf::Vector2f Tetromino::getCenter() const
{
	return mCenter;
}

void Tetromino::setCenter(sf::Vector2f& center)
{
	mCenter = center;
}
