#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include<SFML/Graphics.hpp>
#include "../entities/Tetromino.h"
#include "../util/GameScreen.h"
#include "../input/Player.h"

class Application
{
private:
	enum DirectionControl {
		UP,
		DOWN,
		LEFT,
	};

public:
	Application();
	void run();
private:
	void processInput();
	void update(sf::Time dt);
	void render();
	void updateStatistics(sf::Time dt);
	void registerStates();
private:
	static const float		PlayerSpeed;
	static const sf::Time		TimePerFrame;

	Player		mPlayer;
	sf::RenderWindow			mWindow;
	GameScreen							mGameScreen;
};
#endif // !APPLICATION_H

