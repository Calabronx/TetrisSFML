#include "DataTables.h"

std::vector<TetrominoData> initializeTetrominoData()
{
	std::vector<TetrominoData> data;

	data.resize(10);

	sf::Vertex lShapevrtx1(sf::Vector2f(25, 25), sf::Color::Red);
	sf::Vertex lShapevrtx2(sf::Vector2f(25, 75), sf::Color::Red);
	sf::Vertex lShapevrtx3(sf::Vector2f(0, 75), sf::Color::Red);
	sf::Vertex lShapevrtx4(sf::Vector2f(0, 50), sf::Color::Red);
	sf::Vertex lShapevrtx5(sf::Vector2f(0, 25), sf::Color::Red);

	sf::Vertex lShapevrtx6(sf::Vector2f(0, 0), sf::Color::Red);
	sf::Vertex lShapevrtx7(sf::Vector2f(50, 0), sf::Color::Red);
	sf::Vertex lShapevrtx8(sf::Vector2f(50, 25), sf::Color::Red);

	std::array<sf::Vertex, 8> lVertices = {
		lShapevrtx1, lShapevrtx2, lShapevrtx3,
		lShapevrtx4, lShapevrtx5, lShapevrtx6,
		lShapevrtx7, lShapevrtx8
	};

	data[Tetromino::L].vertices = lVertices;

	sf::Vertex tShapeVrtx1(sf::Vector2f(20, 25), sf::Color::Blue);
	sf::Vertex tShapeVrtx2(sf::Vector2f(0, 25), sf::Color::Blue);
	sf::Vertex tShapeVrtx3(sf::Vector2f(0, 0), sf::Color::Blue);
	sf::Vertex tShapeVrtx4(sf::Vector2f(75, 0), sf::Color::Blue);
	sf::Vertex tShapeVrtx5(sf::Vector2f(75, 25), sf::Color::Blue);

	sf::Vertex tShapeVrtx6(sf::Vector2f(50, 25), sf::Color::Blue);
	sf::Vertex tShapeVrtx7(sf::Vector2f(50, 50), sf::Color::Blue);
	sf::Vertex tShapeVrtx8(sf::Vector2f(25, 50), sf::Color::Blue);

	std::array<sf::Vertex, 8> tVertices = {
		tShapeVrtx1, tShapeVrtx2, tShapeVrtx3,
		tShapeVrtx4, tShapeVrtx5, tShapeVrtx6,
		tShapeVrtx7, tShapeVrtx8
	};

	data[Tetromino::T].vertices = tVertices;

	/*sf::Vertex squareShapeVrtx1(sf::Vector2f(25, 25), sf::Color::Yellow);
	sf::Vertex squareShapeVrtx2(sf::Vector2f(0, 50), sf::Color::Yellow);
	sf::Vertex squareShapeVrtx3(sf::Vector2f(50, 50), sf::Color::Yellow);
	sf::Vertex squareShapeVrtx4(sf::Vector2f(50, 0), sf::Color::Yellow);
	sf::Vertex squareShapeVrtx5(sf::Vector2f(0, 0), sf::Color::Yellow);

	sf::Vertex squareShapeVrtx6(sf::Vector2f(0, 50), sf::Color::Yellow);
	sf::Vertex squareShapeVrtx7(sf::Vector2f(50, 50), sf::Color::Yellow);
	sf::Vertex squareShapeVrtx8(sf::Vector2f(50, 0), sf::Color::Yellow);*/

	/*std::array<sf::Vertex, 8> squareVertices = {
		squareShapeVrtx1, squareShapeVrtx2, squareShapeVrtx3,
		squareShapeVrtx4, squareShapeVrtx5, squareShapeVrtx6,
		squareShapeVrtx7, squareShapeVrtx8
	};*/

	sf::Vertex squareShapeVrtx1(sf::Vector2f(0.f, 0.f), sf::Color::Yellow);
	sf::Vertex squareShapeVrtx2(sf::Vector2f(50.f, 0.f), sf::Color::Yellow);
	sf::Vertex squareShapeVrtx3(sf::Vector2f(50.f, 50.f), sf::Color::Yellow);
	sf::Vertex squareShapeVrtx4(sf::Vector2f(0.f, 50.f), sf::Color::Yellow);

	std::array<sf::Vertex, 8> squareVertices = {
		squareShapeVrtx1, squareShapeVrtx2, squareShapeVrtx3,
		squareShapeVrtx4
	};
	

	data[Tetromino::O].vertices = squareVertices;


	sf::Vertex straightShapeVrtx1(sf::Vector2f(12, 50), sf::Color::Cyan);
	sf::Vertex straightShapeVrtx2(sf::Vector2f(0, 100), sf::Color::Cyan);
	sf::Vertex straightShapeVrtx3(sf::Vector2f(25, 100), sf::Color::Cyan);
	sf::Vertex straightShapeVrtx4(sf::Vector2f(25, 0), sf::Color::Cyan);
	sf::Vertex straightShapeVrtx5(sf::Vector2f(0, 0), sf::Color::Cyan);

	sf::Vertex straightShapeVrtx6(sf::Vector2f(0, 100), sf::Color::Cyan);
	//sf::Vertex squareShapeVrtx7(sf::Vector2f(50, 50), sf::Color::Yellow);
	//sf::Vertex squareShapeVrtx8(sf::Vector2f(50, 0), sf::Color::Yellow);

	std::array<sf::Vertex, 8> straightVertices = {
		straightShapeVrtx1, straightShapeVrtx2, straightShapeVrtx3,
		straightShapeVrtx4, straightShapeVrtx5, straightShapeVrtx6
	};

	data[Tetromino::S].vertices = straightVertices;

	sf::Vertex skewShapeVrtx1(sf::Vector2f(50, 75), sf::Color::Green);
	sf::Vertex skewShapeVrtx2(sf::Vector2f(25, 100), sf::Color::Green);
	sf::Vertex skewShapeVrtx3(sf::Vector2f(50, 100), sf::Color::Green);

	sf::Vertex skewShapeVrtx4(sf::Vector2f(75, 100), sf::Color::Green);

	sf::Vertex skewShapeVrtx5(sf::Vector2f(75, 75), sf::Color::Green);
	sf::Vertex skewShapeVrtx6(sf::Vector2f(75, 50), sf::Color::Green);
	sf::Vertex skewShapeVrtx7(sf::Vector2f(50, 50), sf::Color::Green);

	sf::Vertex skewShapeVrtx8(sf::Vector2f(25, 75), sf::Color::Green);


	//sf::Vertex squareShapeVrtx7(sf::Vector2f(50, 50), sf::Color::Yellow);
	//sf::Vertex squareShapeVrtx8(sf::Vector2f(50, 0), sf::Color::Yellow);

	std::array<sf::Vertex, 8> skewVertices = {
		skewShapeVrtx1, skewShapeVrtx2, skewShapeVrtx3,
		skewShapeVrtx4, skewShapeVrtx5, skewShapeVrtx6,
		skewShapeVrtx7, skewShapeVrtx8
	};

	data[Tetromino::Z].vertices = skewVertices;


	return data;
}
