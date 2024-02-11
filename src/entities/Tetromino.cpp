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
	, mVertices(TetrominoTable[type].vertices)
	, mTransform()
{
	for (auto i = 0; i < mVertices.size(); i++) {
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

void Tetromino::rotate()
{
	std::cout << "rotating" << std::endl;
	mTransform.rotate(20.f);
	mTransform.transformPoint(mPosition);
}

void Tetromino::destroy()
{
}
