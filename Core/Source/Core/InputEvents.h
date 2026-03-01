#pragma once

#include "Event.h"

#include <format>

namespace Core {
	//
	// Mouse Events
	//

	class MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; };
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		// Returns the event's specification
		std::string ToString() const override
		{
			return std::format("Mouse button pressed: {}", m_Button);
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};
}