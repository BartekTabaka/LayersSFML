#pragma once

#include "MySprite.h"

#include <SFML/Graphics.hpp>
#include <functional>
#include <string_view>

namespace Core
{
	class Button : public MySprite {
	public:
		using ClickCallback = std::function<void(Button&)>;
		Button(std::string_view name, const sf::Texture& texture, ClickCallback onClick);

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
		ClickCallback m_ClickCallback;

		const float m_HoverFactor = 1.2f;
	};
}
