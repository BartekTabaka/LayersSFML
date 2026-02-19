#pragma once

#include <SFML/Graphics.hpp>

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
	void Create();
	void Destroy();

	bool IsOpen() const;
	std::optional<sf::Event> pollEvent();

	void Clear(sf::Color clearColor = sf::Color::Black);
	void Display();
private:
	WindowSpecification m_Specification;
	sf::ContextSettings m_ContextSettings;
	sf::RenderWindow m_Window;
};