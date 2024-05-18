#include "DataTables.h"

std::vector<TetrominoData> initializeTetrominoData()
{
	std::vector<TetrominoData> data;

	data.resize(10);

	// Izquierda
	sf::Vertex l1(sf::Vector2f(0.f, 0.f), sf::Color::White);
	sf::Vertex l2(sf::Vector2f(23.5f, 0.f), sf::Color::Red);
	sf::Vertex l3(sf::Vector2f(23.5f, 23.5f), sf::Color::Red);
	sf::Vertex l4(sf::Vector2f(0.f, 23.5f), sf::Color::Red);

	sf::Vertex l5(sf::Vector2f(0.f, 25.f), sf::Color::White);
	sf::Vertex l6(sf::Vector2f(23.5f, 25.f), sf::Color::Red);
	sf::Vertex l7(sf::Vector2f(23.5f, 48.5f), sf::Color::Red);
	sf::Vertex l8(sf::Vector2f(0.f, 48.5f), sf::Color::Red);

	sf::Vertex l9(sf::Vector2f(0.f, 50.f), sf::Color::White);
	sf::Vertex l10(sf::Vector2f(23.5f, 50.f), sf::Color::Red);
	sf::Vertex l11(sf::Vector2f(23.5f, 72.f), sf::Color::Red);
	sf::Vertex l12(sf::Vector2f(0.f, 72.f), sf::Color::Red);

	// Derecha
	sf::Vertex l13(sf::Vector2f(25.f, 50.f), sf::Color::White);
	sf::Vertex l14(sf::Vector2f(48.5f, 50.f), sf::Color::Red);
	sf::Vertex l15(sf::Vector2f(48.5f, 72.f), sf::Color::Red);
	sf::Vertex l16(sf::Vector2f(25.f, 72.f), sf::Color::Red);

	std::array<sf::Vertex, 16> lVertices = {
		l1, l2, l3, l4,
		l5, l6, l7, l8,
		l9, l10, l11, l12,
		l13, l14, l15, l16
	};


	data[Tetromino::L].vertices = lVertices;

	// Izquierda

	sf::Vertex t1(sf::Vector2f(0, 0), sf::Color::White);
	sf::Vertex t2(sf::Vector2f(23.5f, 0.f), sf::Color::Blue);
	sf::Vertex t3(sf::Vector2f(23.5f, 23.5f), sf::Color::Blue);
	sf::Vertex t4(sf::Vector2f(0.f, 23.5f), sf::Color::Blue);


	// Centro

	sf::Vertex t5(sf::Vector2f(25.f, 0.f), sf::Color::White);
	sf::Vertex t6(sf::Vector2f(48.5f, 0.f), sf::Color::Blue);
	sf::Vertex t7(sf::Vector2f(48.5f, 23.5f), sf::Color::Blue);
	sf::Vertex t8(sf::Vector2f(25.f, 23.5f), sf::Color::Blue);


	// Derecha

	sf::Vertex t9(sf::Vector2f(50.f, 0.f), sf::Color::White);
	sf::Vertex t10(sf::Vector2f(73.5f, 0.f), sf::Color::Blue);
	sf::Vertex t11(sf::Vector2f(73.5f, 23.5f), sf::Color::Blue);
	sf::Vertex t12(sf::Vector2f(50.f, 23.5f), sf::Color::Blue);

	// Abajo

	sf::Vertex t13(sf::Vector2f(25.f, 25.f), sf::Color::White);
	sf::Vertex t14(sf::Vector2f(48.5f, 25.f), sf::Color::Blue);
	sf::Vertex t15(sf::Vector2f(48.5f, 48.5f), sf::Color::Blue);
	sf::Vertex t16(sf::Vector2f(25.f, 48.5f), sf::Color::Blue);

	std::array<sf::Vertex, 16> tVertices = {
		t1, t2, t3, t4, t5,
		t6,t7,t8,t9,t10,t11,
		t12,t13,t14,t15,t16
	};

	data[Tetromino::T].vertices = tVertices;

	// Izquierda
	sf::Vertex o1(sf::Vector2f(0.f, 25.f), sf::Color::White);
	sf::Vertex o2(sf::Vector2f(23.5f, 25.f), sf::Color::Yellow);
	sf::Vertex o3(sf::Vector2f(23.5f, 48.5f), sf::Color::Yellow);
	sf::Vertex o4(sf::Vector2f(0.f, 48.5f), sf::Color::Yellow);

	sf::Vertex o5(sf::Vector2f(0.f, 50.f), sf::Color::White);
	sf::Vertex o6(sf::Vector2f(23.5f, 50.f), sf::Color::Yellow);
	sf::Vertex o7(sf::Vector2f(23.5f, 72.f), sf::Color::Yellow);
	sf::Vertex o8(sf::Vector2f(0.f, 72.f), sf::Color::Yellow);

	// Derecha
	sf::Vertex o9(sf::Vector2f(25.f, 50.f), sf::Color::White);
	sf::Vertex o10(sf::Vector2f(48.5f, 50.f), sf::Color::Yellow);
	sf::Vertex o11(sf::Vector2f(48.5f, 72.f), sf::Color::Yellow);
	sf::Vertex o12(sf::Vector2f(25.f, 72.f), sf::Color::Yellow);

	sf::Vertex o13(sf::Vector2f(25.f, 25.f), sf::Color::White);
	sf::Vertex o14(sf::Vector2f(48.5f, 25.f), sf::Color::Yellow);
	sf::Vertex o15(sf::Vector2f(48.5f, 48.f), sf::Color::Yellow);
	sf::Vertex o16(sf::Vector2f(25.f, 48.f), sf::Color::Yellow);

	std::array<sf::Vertex, 16> oVertices = {
		o1, o2, o3, o4,
		o5, o6, o7, o8,
		o9, o10, o11, o12,
		o13, o14, o15, o16
	};


	data[Tetromino::O].vertices = oVertices;




	//sf::Vertex straightShapeVrtx1(sf::Vector2f(12, 50), sf::Color::Cyan);
	//sf::Vertex straightShapeVrtx2(sf::Vector2f(0, 100), sf::Color::White);
	//sf::Vertex straightShapeVrtx3(sf::Vector2f(25, 100), sf::Color::Green);
	//sf::Vertex straightShapeVrtx4(sf::Vector2f(25, 0), sf::Color::Red);
	//sf::Vertex straightShapeVrtx5(sf::Vector2f(0, 0), sf::Color::Yellow);

	//sf::Vertex straightShapeVrtx6(sf::Vector2f(0, 100), sf::Color::Black);
	////sf::Vertex squareShapeVrtx7(sf::Vector2f(50, 50), sf::Color::Yellow);
	////sf::Vertex squareShapeVrtx8(sf::Vector2f(50, 0), sf::Color::Yellow);

	//std::array<sf::Vertex, 8> straightVertices = {
	//	straightShapeVrtx1, straightShapeVrtx2, straightShapeVrtx3,
	//	straightShapeVrtx4, straightShapeVrtx5, straightShapeVrtx6
	//};

	// Izquierda
	sf::Vertex s1(sf::Vector2f(0.f, 25.f), sf::Color::White);
	sf::Vertex s2(sf::Vector2f(23.5f, 25.f), sf::Color::Cyan);
	sf::Vertex s3(sf::Vector2f(23.5f, 48.5f), sf::Color::Cyan);
	sf::Vertex s4(sf::Vector2f(0.f, 48.5f), sf::Color::Cyan);

	sf::Vertex s5(sf::Vector2f(0.f, 50.f), sf::Color::White);
	sf::Vertex s6(sf::Vector2f(23.5f, 50.f), sf::Color::Cyan);
	sf::Vertex s7(sf::Vector2f(23.5f, 73.f), sf::Color::Cyan);
	sf::Vertex s8(sf::Vector2f(0.f, 73.f), sf::Color::Cyan);

	// Derecha
	sf::Vertex s9(sf::Vector2f(0.f, 75.f), sf::Color::White);
	sf::Vertex s10(sf::Vector2f(23.5f, 75.f), sf::Color::Cyan);
	sf::Vertex s11(sf::Vector2f(23.5f, 98.f), sf::Color::Cyan);
	sf::Vertex s12(sf::Vector2f(0.f, 98.f), sf::Color::Cyan);

	sf::Vertex s13(sf::Vector2f(0.f, 100.f), sf::Color::White);
	sf::Vertex s14(sf::Vector2f(23.5f, 100.f), sf::Color::Cyan);
	sf::Vertex s15(sf::Vector2f(23.5f, 123.f), sf::Color::Cyan);
	sf::Vertex s16(sf::Vector2f(0.f, 123.f), sf::Color::Cyan);

	std::array<sf::Vertex, 16> sVertices = {
		s1, s2, s3, s4,
		s5, s6, s7, s8,
		s9, s10, s11, s12,
		s13, s14, s15, s16
	};


	data[Tetromino::S].vertices = sVertices;

	// Izquierda
	sf::Vertex z1(sf::Vector2f(0.f, 0.f), sf::Color::White);
	sf::Vertex z2(sf::Vector2f(23.5f, 0.f), sf::Color::Green);
	sf::Vertex z3(sf::Vector2f(23.5f, 23.5f), sf::Color::Green);
	sf::Vertex z4(sf::Vector2f(0.f, 23.5f), sf::Color::Green);

	sf::Vertex z5(sf::Vector2f(0.f, 25.f), sf::Color::White);
	sf::Vertex z6(sf::Vector2f(23.5f, 25.f), sf::Color::Green);
	sf::Vertex z7(sf::Vector2f(23.5f, 48.f), sf::Color::Green);
	sf::Vertex z8(sf::Vector2f(0.f, 48.f), sf::Color::Green);

	// Derecha
	sf::Vertex z9(sf::Vector2f(25.f, 25.f), sf::Color::White);
	sf::Vertex z10(sf::Vector2f(48.5f, 25.f), sf::Color::Green);
	sf::Vertex z11(sf::Vector2f(48.5f, 48.f), sf::Color::Green);
	sf::Vertex z12(sf::Vector2f(25.f, 48.f), sf::Color::Green);

	sf::Vertex z13(sf::Vector2f(25.f, 50.f), sf::Color::White);
	sf::Vertex z14(sf::Vector2f(48.5f, 50.f), sf::Color::Green);
	sf::Vertex z15(sf::Vector2f(48.5f, 73.f), sf::Color::Green);
	sf::Vertex z16(sf::Vector2f(25.f, 73.f), sf::Color::Green);

	std::array<sf::Vertex, 16> zVertices = {
		z1, z2, z3, z4,
		z5, z6, z7, z8,
		z9, z10, z11, z12,
		z13, z14, z15, z16
	};



	data[Tetromino::Z].vertices = zVertices;


	return data;
}
