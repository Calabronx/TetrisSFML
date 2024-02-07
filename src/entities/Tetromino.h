#pragma once
#ifndef TETROMINO_H
#define TETROMINO_H

#include "Entity.h"

/**
	obj definir clase tetromino para extender y manejar
	los datos de un tetromino
	sus funcionalidades
	
	attributos:
		sprite
		color
		tamaño

		tipo(forma)

	funcionalidad
	rotar
**/

class Tetromino : public Entity
{

public:
	//struct TetrominoStruct {
	//	sf::RectangleShape sprite;
	//	sf::Color color;
	//	int size;
	//};

public:
	explicit								Tetromino();
										Tetromino(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	sf::RectangleShape  mShape;
	sf::Vector2f		mPosition;

private:

	void rotate();
	void destroy();

private:
	sf::Vector2f		mSize;
	sf::Color			mColor;

};

#endif // !TETROMINO_H

