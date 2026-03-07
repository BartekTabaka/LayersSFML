#include "Window.h"
#include <print>
namespace Core {
	Window::Window(const WindowSpecification& specification)
		: m_Specification(specification)
	{
		m_ContextSettings.antiAliasingLevel = 8;
		m_Window.setFramerateLimit(60);
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		m_Window.create(
			sf::VideoMode({ m_Specification.Width, m_Specification.Height }),
			m_Specification.Title,
			m_Specification.Style,
			m_Specification.State,
			m_ContextSettings
		);
	}

	void Window::Destroy()
	{
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

	Vec2f Window::GetMousePosWindow() const
	{
		Vec2i mousePos = sf::Mouse::getPosition(m_Window);
		return static_cast<Vec2f>(mousePos);
	}

	Vec2f Window::GetMousePosScreen() const
	{
		Vec2i mousePos = sf::Mouse::getPosition();
		return static_cast<Vec2f>(mousePos);
	}

	void Window::Clear(sf::Color clearColor)
	{
		m_Window.clear(clearColor);
	}

	void Window::Draw(sf::Drawable& obj)
	{
		m_Window.draw(obj);
	}

	void Window::Display()
	{
		m_Window.display();
	}
}
