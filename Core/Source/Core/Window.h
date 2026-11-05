#pragma once

#include <SFML/Graphics.hpp>

namespace Core {
	// Window properties
	struct WindowSpecification {
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
		sf::Vector2f getSize() const;
		// Get current mouse position inside of the window
		sf::Vector2f getMousePosWindow() const;
		// Get current global mouse position (on screen)
		sf::Vector2f getMousePosScreen() const;

		void clear(sf::Color clearColor = sf::Color::Black);
		void draw(sf::Drawable& obj);
		void display();
	private:
		WindowSpecification m_Specification;
		sf::ContextSettings m_ContextSettings;
		sf::RenderWindow m_Window;
	};
}
