#include "Window.h"

#include <print>

namespace Core 
{
	Window::Window(const WindowSpecification& specification)
		: m_Specification(specification)
	{
		m_ContextSettings.antiAliasingLevel = 8;
		m_Window.setFramerateLimit(60);
	}

	Window::~Window()
	{
		destroy();
	}

	void Window::create()
	{
		m_Window.create(
			sf::VideoMode({ m_Specification.Width, m_Specification.Height }),
			m_Specification.Title,
			m_Specification.Style,
			m_Specification.State,
			m_ContextSettings
		);
	}

	void Window::destroy()
	{
		if (m_Window.isOpen()) {
			m_Window.close();
		}
	}
	
	void Window::draw(sf::Drawable& obj)
	{
		m_Window.draw(obj);
	}

	bool Window::isOpen() const
	{
		return m_Window.isOpen();
	}

	std::optional<sf::Event> Window::pollEvent()
	{
		return m_Window.pollEvent();
	}

	sf::Vector2f Window::getSize() const
	{
		const sf::Vector2u size = m_Window.getSize();
		return static_cast<sf::Vector2f>(size);
	}

	sf::Vector2f Window::getMousePosWindow() const
	{
		const sf::Vector2i mousePos = sf::Mouse::getPosition(m_Window);
		return static_cast<sf::Vector2f>(mousePos);
	}

	sf::Vector2f Window::getMousePosScreen() const
	{
		const sf::Vector2i mousePos = sf::Mouse::getPosition();
		return static_cast<sf::Vector2f>(mousePos);
	}

	void Window::clear(sf::Color clearColor)
	{
		m_Window.clear(clearColor);
	}

	void Window::display()
	{
		m_Window.display();
	}
}
