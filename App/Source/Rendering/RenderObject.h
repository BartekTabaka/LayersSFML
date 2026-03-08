#pragma once

#include <functional>
#include <print>
#include <SFML/Graphics.hpp>

class RenderObject : public sf::Drawable {
public:
	virtual ~RenderObject() = default;

	// Transforms
	virtual sf::FloatRect GetGlobalBounds() const = 0;
};

class MySprite : public RenderObject, public sf::Transformable {
public:
	MySprite(const sf::Texture& texture)
		: m_Sprite(texture)
	{
	}

	void SetColor(sf::Color color)
	{
		m_Sprite.setColor(color);
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return getTransform().transformRect(m_Sprite.getLocalBounds());
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.transform *= getTransform();
		target.draw(m_Sprite, states);
	}
private:
	sf::Sprite m_Sprite;
};

class Button : public RenderObject, public sf::Transformable {
public:
	Button(const sf::Texture& texture, std::function<void()> onClick)
		: m_Sprite(texture), m_OnClick(std::move(onClick))
	{
		auto b = m_Sprite.getLocalBounds();
		//m_Sprite.setOrigin({ b.size.x / 2.f, b.size.y / 2.f });
	}

	void UpdateHover(const sf::Vector2f& mousePos)
	{
		bool now = GetGlobalBounds().contains(mousePos);

		if (now && !m_IsHovered) OnHover();
		else if (!now && m_IsHovered) OnDehover();

		m_IsHovered = now;
	}

	void OnClick()
	{
		if (m_OnClick) m_OnClick();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return getTransform().transformRect(m_Sprite.getLocalBounds());
	}
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.transform *= getTransform();
		target.draw(m_Sprite, states);
	}

	void OnHover()
	{
		std::println("Hovered!");
		m_Sprite.setColor(sf::Color::Red);
		setScale(m_HoveredScale);
	}

	void OnDehover()
	{
		std::println("Dehovered!");
		m_Sprite.setColor(sf::Color::White);
		setScale(m_NormalScale);
	}
private:
	sf::Sprite m_Sprite;

	bool m_IsHovered = false;
	std::function<void()> m_OnClick;
	const sf::Vector2f m_NormalScale = { 1.f, 1.f };
	const sf::Vector2f m_HoveredScale = { 1.2f, 1.2f };
};
