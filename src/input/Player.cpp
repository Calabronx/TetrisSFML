#include "Player.h"
#include "../input/CommandQueue.h"
#include "../entities/Tetromino.h"

#include<SFML/Graphics.hpp>
#include <iostream>

struct TetrominoMover
{
	TetrominoMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (Tetromino& tetromino, sf::Time) const
	{
		tetromino.moveEntity(velocity); // deberia ser otra funcion, para mover el tetromino como el accelerate en el libro SFML
	}

	sf::Vector2f velocity;
};


Player::Player()
{
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

	// Set initial action bindings
	initializeActions();

	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerTetromino;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		std::cout << "event" << std::endl;
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	for (auto pair : mKeyBinding)
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
					mKeyBinding.erase(itr++);
		else
					++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
		if (pair.second == action)
			return pair.first;

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	const float playerSpeed = 200.f;

	mActionBinding[MoveLeft].action	 = derivedAction<Tetromino>(TetrominoMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Tetromino>(TetrominoMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action	 = derivedAction<Tetromino>(TetrominoMover(0.f , -playerSpeed));
	mActionBinding[MoveDown].action	 = derivedAction<Tetromino>(TetrominoMover(0.f , +playerSpeed));
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
			case MoveLeft:
			case MoveRight:
			case MoveDown:
			case MoveUp:
					return true;
			
			default:
				return false;
	}
}
