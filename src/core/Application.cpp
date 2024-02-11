#include "Application.h"
#include <iostream>
#include <array>
#include "../entities/Tetromino.h"

const float Application::PlayerSpeed = 100.f;
const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

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
	mPlayer.setSize(sf::Vector2f(100, 50));
	mPlayer.setOutlineColor(sf::Color::Black);
	mPlayer.setFillColor(sf::Color::Yellow);

	mPlayer.setOutlineThickness(5);
	mPlayer.setPosition(300.f, 100.f);
	//mPlayer.setFillColor(sf::Color::Cyan);

	const int tetrominosCounter = 30;

	std::unique_ptr<Tetromino>lShape(new Tetromino(Tetromino::L));
	std::unique_ptr<Tetromino>tShape(new Tetromino(Tetromino::T));
	std::unique_ptr<Tetromino>oShape(new Tetromino(Tetromino::O));
	std::unique_ptr<Tetromino>sShape(new Tetromino(Tetromino::S));
	std::unique_ptr<Tetromino>zShape(new Tetromino(Tetromino::Z));

	mTetrominos.push_back(std::move(lShape));
	mTetrominos.push_back(std::move(tShape));
	mTetrominos.push_back(std::move(oShape));
	mTetrominos.push_back(std::move(sShape));
	mTetrominos.push_back(std::move(zShape));

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
		}

		if (pos.y >= MAX_FLOOR) {
			mIsFloor = true;
			movement.x = 0;
			movement.y = 0;
			mTetrominosReached.push_back(std::move(mTetrominos[i]));
			std::cout << "size: " << mTetrominosReached.size() << std::endl;
			i++;
		}

		/*std::cout << mTetrominos.size() << std::endl;*/
		if(i < mTetrominos.size())
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
	sf::Vertex vertex;

	vertex.position = sf::Vector2f(10.f, 50.f);

	vertex.color = sf::Color::Red;

	vertex.texCoords = sf::Vector2f(100.f, 100.f);

	//std::cout << mTetrominos.size() << std::endl;
	//sf::VertexArray triangle(sf::Triangles, 3);

	//sf::Vertex vertex(sf::Vector2f(10.f, 50.f), sf::Color::Red, sf::Vector2f(100.f, 100.f)); tambien asi

	mWindow.clear(sf::Color(18, 33, 43)); // Color background

	if (i < mTetrominos.size()) {
		mWindow.draw(mTetrominos[i]->mShape);
	}
	for (int i = 0; i < mTetrominosReached.size(); i++)
		mWindow.draw(mTetrominosReached[i]->mShape);

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
}

void Application::moveVertexArray(sf::VertexArray& vertexArray, sf::Vector2f offset, sf::Time dt)
{
	for (std::size_t i = 0; i < vertexArray.getVertexCount(); i++) {
		vertexArray[i].position += offset * dt.asSeconds();
	}
}
