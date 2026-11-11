#pragma once

#include "RenderObject.h"

#include <SFML/Graphics.hpp>
#include <string_view>

class MySprite : public RenderObject {
public:
	MySprite(std::string_view name, const sf::Texture& texture);

	void setColor(sf::Color color);

	bool isHit(const sf::Vector2f& point) const override;

	// (Axis-Aligned Bounding Box)
	// AABB in world space (accounts for scaling and rotation)
	sf::FloatRect getGlobalBounds() const override
	{
		return getTransform().transformRect(m_Sprite.getGlobalBounds());
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
protected:
	sf::Sprite m_Sprite;

	bool m_IsHovered = false;
};
