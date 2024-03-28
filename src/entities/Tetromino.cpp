#include "Tetromino.h"
#include "../util/DataTables.h"

namespace {
	const std::vector<TetrominoData> TetrominoTable = initializeTetrominoData();
}

Tetromino::Tetromino(Type type)
	: mShape(sf::TriangleFan)
	, mType(type)
	, mRotation()
	, mAngle(180.0f)
	, mVertices(TetrominoTable[type].vertices)
{
	for (auto i = 0; i < mVertices.size(); i++) {
		mShape.append(mVertices[i]);
		mCenter = findCenter(mShape);
		setRotation(mAngle);
	}
	sf::FloatRect bounds = mShape.getBounds();
	setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Tetromino::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mShape, states);
}

void Tetromino::rotate()
{
	if (mAngle == 0.0f || mAngle == 90.0f || mAngle == 180 || mAngle == 270.0f) {
		mAngle += 90.0f;
	}
	else {
		mAngle = 90.0f;
	}
	setRotation(mAngle);
}

void Tetromino::destroy()
{
	delete(this);
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

sf::FloatRect Tetromino::getBoundingRect() const
{
	return getWorldTransform().transformRect(mShape.getBounds());
}

unsigned int Tetromino::getCategory() const
{
	// tengo que pensar bien como usar esto, estaba pensado para manejar diferentes categorias de objetos, pero tetris solo tiene
	// piezas que se mueven, no enemigos. Quizas podria identificar piezas que tocaron el suelo para dividirlas de las que se mueven
	switch (mType)
	{
	case L:
		return Category::PlayerTetromino;
	}
	return 0;
}