#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include<SFML/Graphics.hpp>
#include "../entities/Tetromino.h"

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
	void moveVertexArray(sf::VertexArray& vertexArray, sf::Vector2f offset, sf::Time dt);
	void testRotation(sf::VertexArray& shape, float angleDegrees, const sf::Vector2f& center);
	sf::Vector2f findCenter(const sf::VertexArray& shape);

private:
	static const float		PlayerSpeed;
	static const sf::Time		TimePerFrame;

	std::vector<std::unique_ptr<Tetromino>> mTetrominos;
	std::vector<std::unique_ptr<Tetromino>> mTetrominosReached;


	sf::RectangleShape		mPlayer;
	sf::RenderWindow		mWindow;
	bool					mIsMovingUp;
	bool					mIsMovingDown;
	bool					mIsMovingRight;
	bool					mIsMovingLeft;
	bool					mIsFloor;
	bool					mIsRotating;

};
#endif // !APPLICATION_H

