#pragma once
#ifndef SPRITENODE_H
#define SPRITENODE_H

#include "SceneNode.h"

#include<SFML/Graphics/VertexArray.hpp>

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode();

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::VertexArray		mSprite;
};
#endif // !SPRITENODE_H

