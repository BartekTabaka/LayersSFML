#pragma once

#include "Event.h"

#include <format>

namespace Core 
{
	//
	// Mouse Events
	//

	// Mouse event interface class
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
		}

		std::string toString() const override
		{
			return std::format("Mouse button pressed: {} at x:{}, y:{}", 
				m_Button, m_MousePos.x, m_MousePos.y
			);
		}
	};
}
