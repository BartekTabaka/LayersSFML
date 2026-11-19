#include "Window.h"

#include "Application.h"
#include "InputEvents.h"
#include "WindowEvents.h"

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
	
	void Window::processEvents()
	{
		// NOTE: Keyboard events are processed before window events so that pressing Escape
		// is registered as a KeyPressedEvent before triggering WindowCloseEvent.

		while (const std::optional pollEvent = m_Window.pollEvent()) {
			// Keyboard events
			if (pollEvent->is<sf::Event::KeyPressed>()) {
				const auto key = pollEvent->getIf<sf::Event::KeyPressed>()->code;
				KeyPressedEvent event(key);
				Application::get().raiseEvent(event);
			}
			if (pollEvent->is<sf::Event::KeyReleased>()) {
				const auto key = pollEvent->getIf<sf::Event::KeyReleased>()->code;
				KeyReleasedEvent event(key);
				Application::get().raiseEvent(event);
			}
			// Mouse events
			if (pollEvent->is<sf::Event::MouseButtonPressed>()) {
				const int pressedButton = static_cast<int>(pollEvent->getIf<sf::Event::MouseButtonPressed>()->button);
				const sf::Vector2f mousePos = getMousePosWindow();
				MouseButtonPressedEvent event(pressedButton, mousePos);
				Application::get().raiseEvent(event);
			}
			if (pollEvent->is<sf::Event::MouseButtonReleased>()) {
				const int releasedButton = static_cast<int>(pollEvent->getIf<sf::Event::MouseButtonReleased>()->button);
				const sf::Vector2f mousePos = getMousePosWindow();
				MouseButtonReleasedEvent event(releasedButton, mousePos);
				Application::get().raiseEvent(event);
			}
			if (pollEvent->is<sf::Event::MouseMoved>()) {
				const sf::Vector2f mousePos = getMousePosWindow();
				MouseMovedEvent event(m_LastMousePos, mousePos);
				m_LastMousePos = mousePos;
				Application::get().raiseEvent(event);
			}
			// Window events
			if (pollEvent->is<sf::Event::Closed>() ||
				(pollEvent->is<sf::Event::KeyPressed>() && pollEvent->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)) {
				WindowCloseEvent event;
				Application::get().raiseEvent(event);
				break;
			}
			if (pollEvent->is<sf::Event::Resized>()) {
				const auto newSize = pollEvent->getIf<sf::Event::Resized>()->size;
				WindowResizeEvent event(newSize);
				Application::get().raiseEvent(event);
			}
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
