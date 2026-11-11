#include "Button.h"

#include <functional>

Button::Button(const sf::Texture& texture, std::function<void()> onClick)
	: MySprite(texture)
{
	m_BaseScale = { 0.7f, 0.7f };
	m_OnClick = std::move(onClick);

	// Sprite only has an origin (centered). Position/scale/rotation are handled by Button (the instance)
	auto bounds = m_Sprite.getGlobalBounds();
	m_Sprite.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

	setScale(m_BaseScale);
	setRotation(sf::degrees(45));
}

void Button::updateHover(const sf::Vector2f& mousePos)
{
	const bool now = isHit(mousePos);

	if (now && !m_IsHovered) onHover();
	else if (!now && m_IsHovered) onDehover();
	
	m_IsHovered = now;
}

void Button::onClick()
{
	if (m_OnClick) m_OnClick();
}

bool Button::isHit(const sf::Vector2f& point) const
{
	// local - the point transformed from world coordinates to the sprite's local coordinate space
	const sf::Vector2f local = getBaseTransform().getInverse().transformPoint(point);
	return m_Sprite.getGlobalBounds().contains(local); // The sprite only has an origin here
}

void Button::setBaseScale(const sf::Vector2f newScale)
{
	m_BaseScale = newScale;
	setScale(m_IsHovered ? m_BaseScale * m_HoverFactor : m_BaseScale);
}

sf::FloatRect Button::getGlobalBounds() const
{
	return getTransform().transformRect(m_Sprite.getGlobalBounds());
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
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

void Button::onHover()
{
	std::println("Hovered!");
	m_Sprite.setColor(sf::Color::Red);
	setScale(m_BaseScale * m_HoverFactor);
}

void Button::onDehover()
{
	std::println("Dehovered!");
	setScale(m_BaseScale);
	m_Sprite.setColor(sf::Color::White);
}

