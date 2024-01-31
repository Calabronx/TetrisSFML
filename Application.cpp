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

void Application::update(sf::Time dt)
{
	sf::Vector2f movement(0.f, 0.f);
	sf::Vector2f pos = mPlayer.getPosition();
	const float MAX_FLOOR = 525.649f;

	/* if (mIsMovingUp)
		 movement.y -= PlayerSpeed;*/
	if (pos.y < MAX_FLOOR)
		movement.y += PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;

	if (pos.y >= MAX_FLOOR) {
		mIsFloor = true;
		sf::RectangleShape tetromino;
		tetromino.setSize(sf::Vector2f(100, 50));
		tetromino.setOutlineColor(sf::Color::Black);
		tetromino.setFillColor(sf::Color::Red);
		tetromino.move(movement * dt.asSeconds());
		tetromino.setOutlineThickness(5);
		tetromino.setPosition(300.f, 100.f);
		mTetrominos.push_back(mPlayer);

	}
	
	std::cout << pos.y << std::endl;
	std::cout << mTetrominos.size() << std::endl;


	mPlayer.move(movement * dt.asSeconds());
	//MAX 521.649
}

void Application::render()
{
	mWindow.clear(sf::Color(18, 33, 43)); // Color background
	mWindow.draw(mPlayer);
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
	if (!mIsFloor) {
		if (key == sf::Keyboard::W)
			mIsMovingUp = isPressed;
		else if (key == sf::Keyboard::S)
			mIsMovingDown = isPressed;
		else if (key == sf::Keyboard::A)
			mIsMovingLeft = isPressed;
		else if (key == sf::Keyboard::D)
			mIsMovingRight = isPressed;
	}
}
