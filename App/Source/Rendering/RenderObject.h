#pragma once

#include <SFML/Graphics.hpp>

#include <functional>
#include <print>

// Draws a rectangle outline in the coordinate space specified by `states` (for hitbox debugging)
inline void drawDebugHitbox(sf::RenderTarget& target, const sf::FloatRect& rect, 
	sf::Color outlineColor, const sf::RenderStates& states = sf::RenderStates::Default)
{
	sf::RectangleShape shape(rect.size);
	shape.setPosition(rect.position);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(-1.f); // Outline inward to avoid expanding the rectangle.
	target.draw(shape, states);
}

class RenderObject : public sf::Drawable, public sf::Transformable {
public:
	// Global hitbox debug drawing toggle
	inline static bool s_DebugHitboxes = true;

	virtual ~RenderObject() = default;

	// -- Transforms ------------
	virtual sf::FloatRect getGlobalBounds() const = 0;

	// Returns current position/rotation/origin + base scale
	virtual sf::Transform getBaseTransform() const
	{
		sf::Transformable base;
		base.setPosition(getPosition());
		base.setRotation(getRotation());
		base.setOrigin(getOrigin());
		base.setScale(m_BaseScale);
		return base.getTransform();
	}

	// Fixed hit detection (works correctly with rotations other than 90°)
	// Independent of the current hover scale
	virtual bool isHit(const sf::Vector2f& point) const = 0;

	// Base scale set externally
	virtual void setBaseScale(const sf::Vector2f newScale)
	{
		m_BaseScale = newScale;
	}
	virtual sf::Vector2f getBaseScale() const { return m_BaseScale; }

	// -- Events ------------
	virtual void onClick() {}
	virtual void updateHover(const sf::Vector2f& mousePos) {}
protected:
	std::function<void()> m_OnClick;
	sf::Vector2f m_BaseScale = { 1.f, 1.f };
};
