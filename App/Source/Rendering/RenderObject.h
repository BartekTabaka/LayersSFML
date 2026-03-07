#pragma once

#include <SFML/Graphics.hpp>

class RenderObject {
	using Vec2f = sf::Vector2f;
public:
	virtual ~RenderObject() = default;
	virtual void Update(float dT) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;
	virtual sf::FloatRect GetGlobalBounds() const = 0;
};

class SpriteObject : public RenderObject {
public:
	SpriteObject(const sf::Texture& texture)
		: m_Sprite(texture)
	{
		m_Sprite.setOrigin({ texture.getSize().x / 2.f, texture.getSize().y / 2.f });
	}

	void Update(float dT) override
	{
	}

	void Render(sf::RenderWindow& window) override
	{
		window.draw(m_Sprite);
	}
private:
	sf::Sprite m_Sprite;
};

class TextObject : public RenderObject {
public:
	TextObject(const sf::Font& font, const std::string& string, unsigned int characterSize)
		: m_Text(font, string, characterSize)
	{
		m_Text.setOrigin({ m_Text.getLocalBounds().size.x / 2.f, m_Text.getLocalBounds().size.y / 2.f });
	}

	void Update(float dT) override
	{
	}

	void Render(sf::RenderWindow& window) override
	{
		window.draw(m_Text);
	}
public:
	float scale = 1.f;
	float rotation = 0.f;
	float outlineThickness = 0.f;
	sf::Color outlineColor = sf::Color::Black;
	sf::Color color = sf::Color::White;
private:
	sf::Text m_Text;
	sf::Font m_Font;
};

class ButtonObject : public RenderObject {
public:
	ButtonObject();
};
