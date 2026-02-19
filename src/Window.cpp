#include "Window.h"

Window::Window(const WindowSpecification& specification) : m_Specification(specification) {
	m_ContextSettings.antiAliasingLevel = 8;
	m_Window.setFramerateLimit(60);
}

void Window::Create() {
	m_Window.create(
		sf::VideoMode({ m_Specification.Width, m_Specification.Height }),
		m_Specification.Title,
		m_Specification.Style,
		m_Specification.State,
		m_ContextSettings
	);
}

void Window::Destroy() {
	if (m_Window.isOpen()) {
		m_Window.close();
	}
}

bool Window::IsOpen() const
{
	return m_Window.isOpen();
}

std::optional<sf::Event> Window::pollEvent()
{
	return m_Window.pollEvent();
}

void Window::Clear(sf::Color clearColor) {
	m_Window.clear(clearColor);
}

void Window::Display() {
	m_Window.display();
}
