#include "MySprite.h"

MySprite::MySprite(std::string_view name, const sf::Texture& texture)
	: m_Sprite(texture)
{
	m_Name = name;
}

void MySprite::setColor(sf::Color color)
{
	m_Sprite.setColor(color);
}

bool MySprite::isHit(const sf::Vector2f& point) const
{
	// local - the point transformed from world coordinates to the sprite's local coordinate space
	const sf::Vector2f local = getBaseTransform().getInverse().transformPoint(point);
	return m_Sprite.getGlobalBounds().contains(local); // The sprite only has an origin here
}

void MySprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_Sprite, states);

	// Exact (rotated) sprite outline - drawn in object space
	if (s_DebugHitboxes)
		drawDebugHitbox(target, m_Sprite.getLocalBounds(), sf::Color::Green, states);
}
