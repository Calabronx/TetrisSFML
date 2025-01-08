#include "Tetromino.h"
#include "../util/DataTables.h"
#include <iostream>

namespace {
	const std::vector<TetrominoData> TetrominoTable = initializeTetrominoData();
}

Tetromino::Tetromino(Type type)
	: mShape(sf::Quads)
	, mType(type)
	, mRotation()
	, mAngle(0.0f)
	, mIsGrounded(false)
	, mVertices(TetrominoTable[type].vertices)
{
	sf::Vector2f min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	sf::Vector2f max(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

	for (auto i = 0; i < mVertices.size(); i++) {
		mShape.append(mVertices[i]);
	}
	mCenter = findCenter(mShape);

	//adjustBoundingBox();

	setRotation(mAngle);

	mRects = constructRectListFromVertices(mShape);
	mGlobalRect = getBoundingBox(mRects);

	sf::Transform transform = getTransform();
	sf::FloatRect tetrominoRectTest = transform.transformRect(mShape.getBounds());
	sf::FloatRect tetrominoRect = transform.transformRect(mGlobalRect);
	setOrigin(tetrominoRect.width / 2, tetrominoRect.height / 2);
}

void Tetromino::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mShape, states);
}

void Tetromino::rotate()
{
	if (mType != O) {
		mAngle += 90.0f;
		if (mAngle >= 360.0f) {
			mAngle -= 360.0f;
		}
		setRotation(mAngle);
	}
}

void Tetromino::destroy()
{
	delete(this);
}

void Tetromino::reachGround()
{
	mIsGrounded = true;
	land();
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
/**
	construir un float rect en base un vector que contiene 4 rects, cada rect cuenta con 4 vertices

	begin
		obtengo el width del primer rect
		obtengo el height del primer rect

		por cada rect a partir del segundo de la lista itero
			obtengo la posicion del rect segun index

**/
sf::FloatRect Tetromino::getBoundingBox(std::vector<sf::FloatRect> rects) const
{
	if (rects.size() == 0)
		return sf::FloatRect();

	float left = rects[0].left;
	float top = rects[0].top;
	float right = rects[0].left + rects[0].width;
	float bottom = rects[0].top + rects[0].height;

	for (std::size_t i = 1; i < rects.size(); ++i) {
		float currentLeft = rects[i].left;
		float currentTop = rects[i].top;
		float currentRight = rects[i].left + rects[i].width;
		float currentBottom = rects[i].top + rects[i].height;

		if (currentLeft < left) left = currentLeft;
		if (currentTop > top) top = currentTop;
		if (currentRight < right) right = currentRight;
		if (currentBottom > bottom) bottom = currentBottom;
	}
	return sf::FloatRect(left, top, right - left, bottom - top);
}

void Tetromino::adjustBoundingBox()
{
	//sf::FloatRect boundingBox = getBoundingBox();

	//sf::Vector2f center(boundingBox.left + boundingBox.width / 2.f, boundingBox.top + boundingBox.height / 2.f);

	//setOrigin(center);

	//for (std::size_t i = 0; i < mShape.getVertexCount(); ++i) {
	//	mShape[i].position -= center;
	//}

}

void Tetromino::setCenter(sf::Vector2f& center)
{
	mCenter = center;
}

void Tetromino::setGlobalRect(sf::FloatRect globalRect)
{
	mGlobalRect = globalRect;
}

bool Tetromino::isTetrominoGrounded() const
{
	return mIsGrounded;
}

void Tetromino::setShapeType(sf::PrimitiveType shapeType)
{
	mShape.setPrimitiveType(shapeType);
}

//sf::FloatRect createFloatRectFromVertices(const std::vector<sf::Vertex>& vertices) {
//	if (vertices.empty()) {
//		return sf::FloatRect();
//	}
//
//	float minX = vertices[0].position.x;
//	float minY = vertices[0].position.y;
//	float maxX = vertices[0].position.x;
//	float maxY = vertices[0].position.y;
//
//	for (const auto& vertex : vertices) {
//		if (vertex.position.x < minX) minX = vertex.position.x;
//		if (vertex.position.x > maxX) maxX = vertex.position.x;
//		if (vertex.position.y < minY) minY = vertex.position.y;
//		if (vertex.position.y > maxY) maxY = vertex.position.y;
//	}
//
//	return sf::FloatRect(minX, minY, maxX - minX, maxY - minY);
//}

sf::FloatRect Tetromino::getBoundingRect() const
{
	return getWorldTransform().transformRect(mGlobalRect);
}

/**
	begin

			por cada vertice del arr
				si el indice es mayor o igual que 4 y el indice es modulo de 4
**/

std::vector<sf::FloatRect> Tetromino::constructRectListFromVertices(const sf::VertexArray& vertexArr)
{
	if (vertexArr.getVertexCount() == 0) {
		return std::vector<sf::FloatRect>();
	}

	int index = 0;
	sf::VertexArray tempVertices(sf::Quads, 4);
	std::vector<sf::FloatRect> tetroShapes;
	for (std::size_t i = 0; i <= vertexArr.getVertexCount(); i++) { // hacer que el index sea <= que la cantidad de vertices esta COMO EL ORTO, pero bueno...
		if (i % 4 == 0 && i >= 4) {
			sf::FloatRect tempRect = tempVertices.getBounds();
			tetroShapes.push_back(tempRect);
			tempVertices.clear();
			tempVertices.resize(4);
			tempVertices.setPrimitiveType(sf::Quads);
			index = 0;
		}
		else {
			sf::Vertex vertex = vertexArr[i];
			sf::Vector2f vecArr(vertex.position.x, vertex.position.y);
			tempVertices[index].position = vecArr;
			index++;
		}
	}
	return tetroShapes;
}


//void Tetromino::updateCurrent(sf::Time dt, CommandQueue& commands)
//{
//	/**
//		si el tetromino esta plantado, dejar de mover la entidad por el tiempo delta
//
//		begin
//			si el tetromino no esta plantado
//				mover entidad
//			sino
//				no mover
//		end
//	**/
//
//	if (!mIsGrounded) {
//		Entity:updateCurrent(dt);
//	}
//}

unsigned int Tetromino::getCategory() const
{
	// tengo que pensar bien como usar esto, estaba pensado para manejar diferentes categorias de objetos, pero tetris solo tiene
	// piezas que se mueven, no enemigos. Quizas podria identificar piezas que tocaron el suelo para dividirlas de las que se mueven
	switch (mType)
	{
	case L:
	case T:
	case O:
	case S:
	case Z:
		if (!mIsGrounded) {
			return Category::PlayerTetromino;
		}
		return Category::LandedTetromino;

	}
	return 0;
}