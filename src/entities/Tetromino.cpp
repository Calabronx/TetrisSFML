#include "Tetromino.h"
#include "../util/DataTables.h"
#include <iostream>

namespace {
	const std::vector<TetrominoData> TetrominoTable = initializeTetrominoData();
}

Tetromino::Tetromino()
{
}

Tetromino::Tetromino(Type type)
	: mShape(sf::TriangleFan)
	, mType(type)
	, mRotation()
	, mVertices(TetrominoTable[type].vertices)
{
	for (auto i = 0; i < mVertices.size(); i++) {
	/*	sf::Vector2f sum(0.f, 0.f);
		sum += mVertices[i].position;
		mPosition = sum;*/
		mShape.append(mVertices[i]);
	}
}

/**
	begin
		obtener la actual posicion del tetromino
		mover en el eje x 180 grados
		setear la nueva posicion
	end
**/

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
