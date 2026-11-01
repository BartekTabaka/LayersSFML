#pragma once

#include "Event.h"

#include <string>
#include <unordered_set>

#include <SFML/Graphics.hpp>

namespace Core {
	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void onEvent(Event& event) {}

		virtual void onUpdate(float ts) {}
		virtual void onRender() {}

		template<std::derived_from<Layer> T, typename... Args>
		void transitionTo(Args&&... args)
		{
			queueTransition(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
		}

		std::string getName() const
		{
			if (!m_Name.empty() || m_Name != "")
				return m_Name;
			else return std::format("[WARNING]: Layer name not specified!");
		}
	private:
		void queueTransition(std::unique_ptr<Layer> toLayer);
	protected:
		std::string m_Name;
		std::unordered_set<EventType> m_EventTypesToHandle;
	};
}
