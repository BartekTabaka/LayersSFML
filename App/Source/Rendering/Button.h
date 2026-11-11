#pragma once

#include "MySprite.h"

#include <SFML/Graphics.hpp>
#include <functional>
#include <string_view>

class Button : public MySprite {
public:
public:
	Button(std::string_view name, const sf::Texture& texture, std::function<void()> onClick);

	void updateHover(const sf::Vector2f& mousePos) override;
	void onClick() override;
	bool isHit(const sf::Vector2f& point) const override;

	// Base scale set externally. Hover is only a multiplier applied to it.
	void setBaseScale(const sf::Vector2f newScale) override;

	// Visual bounds (AABB, accounts for the current scale, including hover)
	sf::FloatRect getGlobalBounds() const override;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void onHover();
	void onDehover();
private:
	const float m_HoverFactor = 1.2f;
};
