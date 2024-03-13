#pragma once
#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/Graphics.hpp>

#include "../util/Category.h"
#include <functional>
#include <cassert>

class SceneNode;
struct Command
{
																							Command();
	std::function<void(SceneNode&, sf::Time)>			action;
	unsigned int														category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return[=](SceneNode& node, sf::Time dt)
	{
		//Check if cast is safe
		assert(dynamic_cast<GameObject*> (&node) != nullptr);

		// downcast node and invoce function on it
		fn(static_cast<GameObject&>(node), dt);

	};
}
#endif

