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
	, mIsGrounded(false)
	, mVertices(TetrominoTable[type].vertices)
{
	sf::Vector2f min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	sf::Vector2f max(std::numeric_limits<float>::min(), std::numeric_limits<float>::min());

	/**
	* calcular el transform de cada vertice y construir un rectanculo exacto de su forma
	*
	* begin
	*		sumar todos los vertices
	*		obtener transform
			transformar punto del vertice y asignar a un vector
			definir float rect con parametros del vector de vertices
			setear parametros al origin del tetromino
		end

	**/
	sf::Vector2f vertexPos;
	for (auto i = 0; i < mVertices.size(); i++) {
		mShape.append(mVertices[i]);
		mCenter = findCenter(mShape);
		setRotation(mAngle);
		vertexPos = mVertices[i].position;

		/*min.x = std::min(min.x, vertexPos.x);
		min.y = std::min(min.y, vertexPos.y);
		max.x = std::max(max.x, vertexPos.x);
		max.y = std::max(max.y, vertexPos.y);*/
	}
	sf::Transform transform = getTransform();
	//sf::Vector2f point = transform.transformPoint(vertexPos.x, vertexPos.y);

	sf::FloatRect tetrominoRect = transform.transformRect(mShape.getBounds());
	setOrigin(tetrominoRect.width / 2.f, tetrominoRect.height / 2.f);
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

void Tetromino::setCenter(sf::Vector2f& center)
{
	mCenter = center;
}

bool Tetromino::isTetrominoGrounded() const
{
	return mIsGrounded;
}


sf::FloatRect Tetromino::getBoundingRect() const
{
	return getWorldTransform().transformRect(mShape.getBounds());
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