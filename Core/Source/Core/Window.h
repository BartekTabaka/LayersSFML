#pragma once

#include <SFML/Graphics.hpp>

namespace Core {
	using Vec2f = sf::Vector2f;
	using Vec2i = sf::Vector2i;
	using Vec2u = sf::Vector2u;

	struct WindowSpecification { // Window properties
		std::string Title = "Layers SFML";
		uint32_t Width = 1280;
		uint32_t Height = 720;
		uint32_t Style = sf::Style::Default;
		sf::State State = sf::State::Windowed;
	};

	class Window {
	public:
		Window(const WindowSpecification& specification);
		~Window();

		void create();
		void destroy();

		bool isOpen() const;
		std::optional<sf::Event> pollEvent();
		Vec2f getSize() const;
		// Get current mouse position inside of the window
		Vec2f getMousePosWindow() const;
		// Get current global mouse position (on screen)
		Vec2f getMousePosScreen() const;

		void clear(sf::Color clearColor = sf::Color::Black);
		void draw(sf::Drawable& obj);
		void display();
	private:
		WindowSpecification m_Specification;
		sf::ContextSettings m_ContextSettings;
		sf::RenderWindow m_Window;
	};
}
