#pragma once

#include "Event.h"

#include <SFML/Graphics.hpp>

#include <format>

namespace Core {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(sf::Vector2u newSize)
			: m_WindowSize(newSize) { }

		inline sf::Vector2u getNewSize() const { return m_WindowSize; }
		inline unsigned int getWidth() const { return m_WindowSize.x; }
		inline unsigned int getHeight() const { return m_WindowSize.y; }

		std::string toString() const override
		{
			return std::format("Window resized to - x:{}, y:{}", getWidth(), getHeight());
		}

		EVENT_CLASS_TYPE(WindowResize)
	private:
		sf::Vector2u m_WindowSize;
	};
}
