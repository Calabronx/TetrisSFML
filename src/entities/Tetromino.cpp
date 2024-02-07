#include "Tetromino.h"

Tetromino::Tetromino()
{
}

Tetromino::Tetromino(sf::Vector2f position, sf::Vector2f size, sf::Color color)
	: mShape()
	, mPosition(position)
	, mSize(size)
	, mColor(color)

{
	mShape.setSize(sf::Vector2f(100, 30));
	mShape.setOutlineColor(sf::Color::Black);
	mShape.setFillColor(mColor);
	mShape.setOutlineThickness(5);
	mShape.setPosition(300.f, 50.f);

	//TetrominoStruct *tr = new TetrominoStruct();
}

void Tetromino::rotate()
{
}

void Tetromino::destroy()
{
}
