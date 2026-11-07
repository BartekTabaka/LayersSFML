#pragma once

#include "Event.h"

#include <format>

namespace Core 
{
	//
	// Mouse Events
	//

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(sf::Vector2f mousePos)
			: m_MousePos(mousePos) {}

		inline sf::Vector2f getMousePosition() const { return m_MousePos; };
	
		std::string toString() const override
		{
			return std::format("Mouse moved to - x:{}, y:{}", m_MousePos.x, m_MousePos.y);
		}

		EVENT_CLASS_TYPE(MouseMoved)
	private:
		sf::Vector2f m_MousePos;
	};

	class MouseButtonEvent : public Event {
	public:
		inline int getMouseButton() const { return m_Button; };
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			return std::format("Mouse button pressed: {}", m_Button);
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
}
