#include "SpriteNode.h"

SpriteNode::SpriteNode()
	: mSprite()
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
