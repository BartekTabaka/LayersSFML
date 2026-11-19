#pragma once

#include "Event.h"

#include <SFML/Graphics.hpp>

#include <format>

namespace Core 
{
	//
	// Keyboard Events
	//

	class KeyEvent : public Event {
	public:
		inline sf::Keyboard::Key getKeyCode() const { return m_KeyCode; }
	protected:
		explicit KeyEvent(sf::Keyboard::Key keycode)
			: m_KeyCode(keycode)
		{
		}

		sf::Keyboard::Key m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		EVENT_CLASS_TYPE(KeyPressed)

		KeyPressedEvent(sf::Keyboard::Key keycode)
			: KeyEvent(keycode)
		{
		}

		std::string toString() const override
		{
			return std::format("Key pressed (code): {}", (int)m_KeyCode);
		}
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		EVENT_CLASS_TYPE(KeyReleased)

		KeyReleasedEvent(sf::Keyboard::Key keycode)
			: KeyEvent(keycode)
		{
		}

		std::string toString() const override
		{
			return std::format("Key released (code): {}", (int)m_KeyCode);
		}
	};

	//
	// Mouse Events
	//

	class MouseEvent : public Event {
	public:
		~MouseEvent() = default;
	protected:
		sf::Vector2f m_MousePos;
	};

	class MouseMovedEvent : public MouseEvent {
	public:
		EVENT_CLASS_TYPE(MouseMoved)

		MouseMovedEvent(const sf::Vector2f& fromPos, const sf::Vector2f& toPos)
		{
			m_LastPosition = fromPos;
			m_MousePos = toPos;
			m_Delta = m_MousePos - m_LastPosition;
		}

		inline sf::Vector2f getCurrentMousePosition() const { return m_MousePos; };
		inline sf::Vector2f getLastMousePosition() const { return m_LastPosition; };
		inline sf::Vector2f getDelta() const { return m_Delta; };
	
		std::string toString() const override
		{
			return std::format("Mouse moved from x:{}, y:{} - to x:{}, y:{} (Delta - x:{}, y:{})", 
				m_LastPosition.x, m_LastPosition.y, m_MousePos.x, m_MousePos.y, m_Delta.x, m_Delta.y
			);
		}
	private:
		sf::Vector2f m_LastPosition;
		sf::Vector2f m_Delta;
	};
	
	// -- Mouse buttons ------------
	class MouseButtonEvent : public MouseEvent {
	public:
		~MouseButtonEvent() = default;

		inline int getMouseButton() const { return m_Button; };
		inline sf::Vector2f getMousePosition() const { return m_MousePos; };
	protected:
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		EVENT_CLASS_TYPE(MouseButtonPressed)

		MouseButtonPressedEvent(int button, const sf::Vector2f& position)
		{
			m_Button = button;
			m_MousePos = position;
		}

		std::string toString() const override
		{
			return std::format("Mouse button pressed: {} at x:{}, y:{}", 
				m_Button, m_MousePos.x, m_MousePos.y
			);
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		EVENT_CLASS_TYPE(MouseButtonPressed)

		MouseButtonReleasedEvent(int button, const sf::Vector2f& position)
		{
			m_Button = button;
			m_MousePos = position;
		}

		std::string toString() const override
		{
			return std::format("Mouse button released: {} at x:{}, y:{}", 
				m_Button, m_MousePos.x, m_MousePos.y
			);
		}
	};
}
