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
	inline static bool s_DebugHitboxes = false;

	virtual ~RenderObject() = default;

	// Transforms
	virtual sf::FloatRect getGlobalBounds() const = 0;
};

class MySprite : public RenderObject {
public:
	MySprite(const sf::Texture& texture)
		: m_Sprite(texture)
	{
	}

	void setColor(sf::Color color)
	{
		m_Sprite.setColor(color);
	}

	// (Axis-Aligned Bounding Box)
	// AABB in world space (accounts for scaling and rotation)
	sf::FloatRect getGlobalBounds() const override
	{
		return getTransform().transformRect(m_Sprite.getGlobalBounds());
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.transform *= getTransform();
		target.draw(m_Sprite, states);

		// Exact (rotated) sprite outline - drawn in object space
		if (s_DebugHitboxes)
			drawDebugHitbox(target, m_Sprite.getLocalBounds(), sf::Color::Green, states);
	}
private:
	sf::Sprite m_Sprite;
};

class Button : public RenderObject {
public:
	Button(const sf::Texture& texture, std::function<void()> onClick)
		: m_Sprite(texture), m_OnClick(std::move(onClick))
	{
		// Sprite only has an origin (centered). Position/scale/rotation are handled by Button (the instance)
		auto bounds = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

		setScale(m_BaseScale);
		setRotation(sf::degrees(45));
	}

	void updateHover(const sf::Vector2f& mousePos)
	{
		const bool now = isHit(mousePos);

		if (now && !m_IsHovered) OnHover();
		else if (!now && m_IsHovered) OnDehover();

		m_IsHovered = now;
	}

	void onClick()
	{
		if (m_OnClick) m_OnClick();
	}

	// Base scale set externally. Hover is only a multiplier applied to it.
	void setBaseScale(const sf::Vector2f newScale)
	{
		m_BaseScale = newScale;
		setScale(m_IsHovered ? m_BaseScale * m_HoverFactor : m_BaseScale);
	}

	sf::Vector2f getBaseScale() const { return m_BaseScale; }

	// Returns current button position/rotation/origin + base scale
	sf::Transform getBaseTransform() const
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
	bool isHit(const sf::Vector2f& point) const
	{
		// local - the point transformed from world coordinates to the sprite's local coordinate space
		const sf::Vector2f local = getBaseTransform().getInverse().transformPoint(point);
		return m_Sprite.getGlobalBounds().contains(local); // // The sprite only has an origin here
	}

	// Visual bounds (AABB, accounts for the current scale, including hover)
	sf::FloatRect getGlobalBounds() const override
	{
		return getTransform().transformRect(m_Sprite.getGlobalBounds());
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		const sf::RenderStates worldStates = states;

		states.transform *= getTransform();
		target.draw(m_Sprite, states);

		if (s_DebugHitboxes) {
			// Red: visual bounds - rotated rectangle in object space
			// (uses the current scale, so it grows on hover)
			drawDebugHitbox(target, m_Sprite.getGlobalBounds(), sf::Color::Red, states);

			// Green: actual hitbox (fixed, rotates together with the button)
			sf::RenderStates hitboxStates = worldStates;
			hitboxStates.transform *= getBaseTransform();
			drawDebugHitbox(target, m_Sprite.getGlobalBounds(), sf::Color::Green, hitboxStates);
		}
	}

	void OnHover()
	{
		std::println("Hovered!");
		m_Sprite.setColor(sf::Color::Red);
		setScale(m_BaseScale * m_HoverFactor);
	}

	void OnDehover()
	{
		std::println("Dehovered!");
		m_Sprite.setColor(sf::Color::White);
		setScale(m_BaseScale);
	}
private:
	sf::Sprite m_Sprite;

	bool m_IsHovered = false;
	std::function<void()> m_OnClick;

	sf::Vector2f m_BaseScale = { 0.7f, 0.7f };
	float m_HoverFactor = 1.2f;
};
