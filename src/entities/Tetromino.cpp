#include "Tetromino.h"
#include "../util/DataTables.h"

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
