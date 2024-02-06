#include "Application.h"
#include <iostream>

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

	for (int i = 0; i < 10; i++) {
		sf::RectangleShape tetromino;
		tetromino.setSize(sf::Vector2f(100, 30));
		tetromino.setOutlineColor(sf::Color::Black);
		tetromino.setFillColor(sf::Color::Red);
		tetromino.setOutlineThickness(5);
		tetromino.setPosition(300.f, i + 50.f);
		mTetrominos.push_back(tetromino);
	}

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
		sf::Vector2f pos = mTetrominos[i].getPosition();

		const float MAX_FLOOR = 525.649f;

		if (pos.y < MAX_FLOOR) {
			movement.y += PlayerSpeed;
			if (mIsMovingRight)
				movement.x += PlayerSpeed;
			if (mIsMovingLeft)
				movement.x -= PlayerSpeed;
		}

		if (pos.y >= MAX_FLOOR) {
			mIsFloor = true;
			movement.x = 0;
			movement.y = 0;
			mTetrominosReached.push_back(mTetrominos[i]);
			std::cout << "size: " << mTetrominosReached.size() << std::endl;
			i++;
		}
		mTetrominos[i].move(movement * dt.asSeconds());
	}

	//std::cout << pos.y << std::endl;

	//MAX 521.649
}

void Application::render()
{
	mWindow.clear(sf::Color(18, 33, 43)); // Color background
	//mWindow.draw(mPlayer);

	if (i < mTetrominos.size()) {
		mWindow.draw(mTetrominos[i]);
	}

	for (int i = 0; i < mTetrominosReached.size(); i++)
		mWindow.draw(mTetrominosReached[i]);

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
