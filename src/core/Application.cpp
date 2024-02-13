#include "Application.h"
#include <iostream>
#include <array>
#include "../entities/Tetromino.h"

const float Application::PlayerSpeed = 100.f;
const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

sf::Transform rotation;
sf::Transform transform = rotation;
sf::RectangleShape entity;

Application::Application()
	:mWindow(sf::VideoMode(600, 600), "Window Title", sf::Style::Close)
	, mPlayer()
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingLeft(false)
	, mIsMovingRight(false)
	, mIsFloor(false)
{
	int centerScreen = mWindow.getSize().x / 2;
	/*entity.setPosition(centerScreen, 50.0f);
	entity.setFillColor(sf::Color::Yellow);
	entity.setSize(sf::Vector2f(120, 120));*/
	//mPlayer.setRadius(40.f);
	//mPlayer.setSize(sf::Vector2f(100, 50));
	//mPlayer.setOutlineColor(sf::Color::Black);
	//mPlayer.setFillColor(sf::Color::Yellow);

	//mPlayer.setOutlineThickness(5);
	//mPlayer.setPosition(300.f, 100.f);
	//mPlayer.setFillColor(sf::Color::Cyan);

	const int tetrominosCounter = 30;
	sf::Vector2f centerShape(0.0f, 0.0f);

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

		sf::Vector2f windowSize(600.f,600.f);
		sf::Vector2f centerScreen = windowSize / 2.0f;

		sf::Vector2f tetrominoCenter = findCenter(mTetrominos[i]->mShape);
		sf::Vector2f offsetToCenter = centerScreen - tetrominoCenter;
		sf::Vector2f moveToTop(offsetToCenter.x, offsetToCenter.y - 300.f);



		for (std::size_t j = 0; j < mTetrominos[i]->mShape.getVertexCount(); j++) {
			mTetrominos[i]->mShape[j].position += moveToTop;
		}
	}
	//testRotation();

	/*rotation.rotate(25.0f);

	transform = rotation;*/
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
int rotate = 45;



void Application::update(sf::Time dt)
{
	if (i < mTetrominos.size()) {
		sf::Vector2f movement(0.f, 0.f);
		sf::Transform rotation;
		//rotation.rotate(rotate);
		//rotate++;
		sf::Transform transform = rotation;

		sf::Vector2f pos = mTetrominos[i]->mShape[0].position;
	/*	mTetrominos[i]->mShape[0].position = movement;*/
		Tetromino* tetromino = mTetrominos[i].get();
		const float MAX_FLOOR = 540.649f;

		if (pos.y < MAX_FLOOR) {
			movement.y += PlayerSpeed;
			if (mIsMovingRight)
				movement.x += PlayerSpeed;
			if (mIsMovingLeft)
				movement.x -= PlayerSpeed;
			if (mIsMovingDown)
				movement.y += PlayerSpeed;

			if (mIsRotating)
				tetromino->rotate(transform);
		}
		tetromino->setVelocity(movement);
		tetromino->setTransform(transform);

		//for (std::size_t i = 0; i < mTetrominos[i]->mShape.getVertexCount(); i++) {
		//	mTetrominos[i]->mShape[i].position = center ;
		//}

		//sf::Vector2f Point_BP = transform.transformPoint(PointB);
		//sf::Vector2f Point_CP = transform.transformPoint(PointC);

		//triangle[1].position = Point_BP;
		//triangle[2].position = Point_CP;

		//triangle[0].color = sf::Color(0, 0, 255, 20);
		//triangle[1].color = sf::Color::Blue;
		//triangle[0].color = sf::Color::Blue;

	/*	sf::Vector2f PointA(20.f, 20.f);
		sf::Vector2f PointB(20.f, 20.f);
		sf::Vector2f PointC(20.f, 20.f);
		sf::Vector2f*/


		//entity.move(5.f, 5.f);
	/*	for (std::size_t i = 0; i < mTetrominos[i]->mShape.getVertexCount(); i++) {
			movement = transform.transformPoint(sf::Vector2f(20.f, 20.f));
			mTetrominos[i]->mShape[i].position
		}*/
		//float rotation = entity.getRotation();
		//std::cout << "rotation:" << rotation << std::endl;
		//sf::Vector2f center = findCenter(mTetrominos[0]->mShape);
		//testRotation(mTetrominos[0]->mShape, 45.0f, center);

		//transform.rotate(180.0f, movement);

		/*rotation.rotate(25.0f);*/

		transform = rotation;

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
			moveVertexArray(mTetrominos[i]->mShape, tetromino->getVelocity(), dt);
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
		mWindow.draw(mTetrominos[i]->mShape, transform);
	}
	for (int i = 0; i < mTetrominosReached.size(); i++)
		mWindow.draw(mTetrominosReached[i]->mShape);

	//mWindow.draw(entity);
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

void Application::testRotation(sf::VertexArray& shape, float angleDegrees, const sf::Vector2f& center) {
	float angleRad = angleDegrees * 3.14159265f / 180.0f; // convert degrees to radians
	for (size_t index = 0; index < shape.getVertexCount(); index++) {
		sf::Vector2f point = shape[i].position - center;

		// apply rotation
		float rotatedX = point.x * cos(angleRad) - point.y * sin(angleRad);
		float rotatedY = point.y * sin(angleRad) + point.y * cos(angleRad);

		// translate back and set position
		shape[i].position = sf::Vector2f(rotatedX + center.x, rotatedY + center.y);
	}
}

sf::Vector2f Application::findCenter(const sf::VertexArray& vertices) {
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
