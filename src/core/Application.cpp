#include "Application.h"
#include <iostream>
#include <array>
#include "../entities/Tetromino.h"

const float Application::PlayerSpeed = 100.f;
const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

sf::Transform rotation;
sf::Transform transform = rotation;
sf::VertexArray triangle(sf::Triangles, 3);

sf::Vector2f PointA(350.0f, 350.0f);
sf::Vector2f PointB(250.0f, 340.0f);
sf::Vector2f PointC(250.0f, 360.0f);

Application::Application()
	:mWindow(sf::VideoMode(600, 600), "Window Title", sf::Style::Close)
	, mPlayer()
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingLeft(false)
	, mIsMovingRight(false)
	, mIsFloor(false)
{
	//mPlayer.setRadius(40.f);
	//mPlayer.setSize(sf::Vector2f(100, 50));
	//mPlayer.setOutlineColor(sf::Color::Black);
	//mPlayer.setFillColor(sf::Color::Yellow);

	//mPlayer.setOutlineThickness(5);
	//mPlayer.setPosition(300.f, 100.f);
	//mPlayer.setFillColor(sf::Color::Cyan);

	const int tetrominosCounter = 30;

	for (auto i = 0; i < tetrominosCounter; i++) {
		int randomId = rand() % 5 + 1;

		if (randomId == Tetromino::L) {
			std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::T));
			mTetrominos.push_back(std::move(lShape));
		}
		else if (randomId == Tetromino::T) {
			std::unique_ptr<Tetromino>tShape(new Tetromino(Tetromino::T));
			mTetrominos.push_back(std::move(tShape));
		}
		else if (randomId == Tetromino::O) {
			std::unique_ptr<Tetromino>oShape(new Tetromino(Tetromino::O));
			mTetrominos.push_back(std::move(oShape));
		}
		else if (randomId == Tetromino::S) {
			std::unique_ptr<Tetromino>sShape(new Tetromino(Tetromino::S));
			mTetrominos.push_back(std::move(sShape));

		}
		else if (randomId == Tetromino::Z) {
			std::unique_ptr<Tetromino>zShape(new Tetromino(Tetromino::Z));
			mTetrominos.push_back(std::move(zShape));
		}
		else {
			std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
			mTetrominos.push_back(std::move(lShape));
		}
		//switch (randomId) {
		//case Tetromino::L:
		//	lShape(new Tetromino(Tetromino::T));
		//	break;
		//case Tetromino::T:
		//	//std::unique_ptr<Tetromino>tShape(new Tetromino(Tetromino::T));
		//	break;
		//default:
		//	break;
		//}
	}
	//testRotation();

	//rotation.rotate(10.0f);

	//transform = rotation;

	//triangle[0].position = PointA;
	//triangle[1].position = PointB;
	//triangle[2].position = PointC;

	//triangle[0].color = sf::Color::Blue;
	//triangle[1].color = sf::Color::Blue;
	//triangle[2].color = sf::Color::Blue;

}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		render();
	}
}

//void Application::processInput()
//{
//    sf::Event event;
//    while (mWindow.pollEvent(event))
//    {
//        switch (event.type)
//        {
//        case sf::Event::KeyPressed:
//            handlePlayerInput(event.key.code, true);
//            break;
//        case sf::Event::KeyReleased:
//            handlePlayerInput(event.key.code, false);
//            break;
//            case sf::Event::Closed;
//                mWindow.close();
//                break;
//        }
//    }
//}

void Application::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}


/**
	begin
		iterar por cada tetromino
			mover hacia el piso
				si llega al piso
					setear bandera isFloor
					actualizar index del vector
					agregar a lista de tetrominos inactivos
					dibujar nuevo tetromino
					controlar tetromino
	end
**/

int i = 0;


void Application::update(sf::Time dt)
{
	if (i < mTetrominos.size()) {
		sf::Vector2f movement(0.f, 0.f);
		sf::Vector2f pos = mTetrominos[i]->mShape[i].position;
		Tetromino* tetromino = mTetrominos[i].get();

		const float MAX_FLOOR = 540.649f;

		if (pos.y < MAX_FLOOR) {
			movement.y += PlayerSpeed;
			tetromino->setVelocity(movement);
			if (mIsMovingRight)
				movement.x += PlayerSpeed;
			tetromino->setVelocity(movement);
			if (mIsMovingLeft)
				movement.x -= PlayerSpeed;
			tetromino->setVelocity(movement);
			if (mIsMovingDown)
				movement.y += PlayerSpeed;
			tetromino->setVelocity(movement);

			//if (mIsRotating)
			//	//movement.y += PlayerSpeed;
			//	//tetromino->rotate();
			//	transform = rotation.rotate(0.1f);
			//tetromino->setVelocity(movement);


		}

		//sf::Vector2f Point_BP = transform.transformPoint(PointB);
		//sf::Vector2f Point_CP = transform.transformPoint(PointC);

		//triangle[1].position = Point_BP;
		//triangle[2].position = Point_CP;

		//triangle[0].color = sf::Color(0, 0, 255, 20);
		//triangle[1].color = sf::Color::Blue;
		//triangle[0].color = sf::Color::Blue;

		if (pos.y >= MAX_FLOOR) {
			mIsFloor = true;
			movement.x = 0;
			movement.y = 0;
			mTetrominosReached.push_back(std::move(mTetrominos[i]));
			std::cout << "size: " << mTetrominosReached.size() << std::endl;
			i++;
		}





		/*std::cout << mTetrominos.size() << std::endl;*/
		if (i < mTetrominos.size())
			moveVertexArray(mTetrominos[i]->mShape, movement, dt);
	}

}

/**
	deberia manejar el vertex array para construir los tetrominos
	luego con un enum diferenciar el ID del tetromino en cuestion
	y programar una funcion que elija un id random para dibujar
**/
void Application::render()
{
	mWindow.clear(sf::Color(18, 33, 43)); // Color background

	if (i < mTetrominos.size()) {
		mWindow.draw(mTetrominos[i]->mShape);
	}
	for (int i = 0; i < mTetrominosReached.size(); i++)
		mWindow.draw(mTetrominosReached[i]->mShape);

	//mWindow.draw(triangle);
	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
}

void Application::registerStates()
{
}

void Application::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;

	else if (key == sf::Keyboard::Z)
		mIsRotating = isPressed;

	/*else if (key == sf::Keyboard::Escape)
		std::cout << "QUITTING GAME..." << std::endl;
		exit(0);*/
}

void Application::moveVertexArray(sf::VertexArray& vertexArray, sf::Vector2f offset, sf::Time dt)
{
	for (std::size_t i = 0; i < vertexArray.getVertexCount(); i++) {
		vertexArray[i].position += offset * dt.asSeconds();
	}
}

void testRotation() {
	rotation.rotate(10.0f);

	transform = rotation;

	//sf::Vector2f PointA(350.0f, 350.0f);
	//sf::Vector2f PointB(250.0f, 340.0f);
	//sf::Vector2f PointC(250.0f, 360.0f);

	triangle[0].position = PointA;
	triangle[1].position = PointB;
	triangle[2].position = PointC;

	triangle[0].color = sf::Color::Blue;
	triangle[1].color = sf::Color::Blue;
	triangle[2].color = sf::Color::Blue;


}
