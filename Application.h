#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include<SFML/Graphics.hpp>

class Application
{
public:
	Application();
	void run();
private:
	//void processInput();
	void processEvents();
	void update(sf::Time dt);
	void render();

	void updateStatistics(sf::Time dt);
	void registerStates();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
	static const float		PlayerSpeed;
	static const sf::Time		TimePerFrame;

	sf::CircleShape			mPlayer;
	sf::RenderWindow		mWindow;
	bool					mIsMovingUp;
	bool					mIsMovingDown;
	bool					mIsMovingRight;
	bool					mIsMovingLeft;

};
#endif // !APPLICATION_H

