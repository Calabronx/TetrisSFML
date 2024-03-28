#include "Application.h"
#include <iostream>
#include <array>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: mWindow(sf::VideoMode(640, 480), "Tetris", sf::Style::Close)
	, mGameScreen(mWindow)
	, mPlayer()
{
	mWindow.setKeyRepeatEnabled(false);
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

			processInput();
			update(TimePerFrame);
		}

		render();
	}
}

void Application::processInput()
{
	CommandQueue& commands = mGameScreen.getCommandQueue();

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mPlayer.handleEvent(event, commands);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}

	mPlayer.handleRealtimeInput(commands);
}

void Application::update(sf::Time dt)
{
	mGameScreen.update(dt);
}

void Application::render()
{
	mWindow.clear(sf::Color(18, 33, 43)); // Color background

	mGameScreen.draw();
	mWindow.setView(mWindow.getDefaultView());

	mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
}

void Application::registerStates()
{
}




