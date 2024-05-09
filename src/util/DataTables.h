#pragma once
#ifndef DATA_TABLES_H
#define DATA_TABLES_H

#include<SFML/Graphics.hpp>

#include<vector>
#include "../entities/Tetromino.h"

class Tetromino;

struct TetrominoData {
		std::array<sf::Vertex, 8> vertices;
		sf::Color color;
		int lifes;
};

std::vector<TetrominoData>			initializeTetrominoData();
#endif // !DATA_TABLES_H

