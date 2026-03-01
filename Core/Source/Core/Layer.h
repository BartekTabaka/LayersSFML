#pragma once

#include "Event.h"

#include <string>
#include <unordered_set>

#include <SFML/Graphics.hpp>

namespace Core {
	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void OnEvent(Event& event) {}

		virtual void OnUpdate(float ts) {}
		virtual void OnRender() {}

		template<std::derived_from<Layer> T, typename... Args>
		void TransitionTo(Args&&... args)
		{
			QueueTransition(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
		}

		std::string GetName() const
		{
			if (!m_Name.empty() || m_Name != "")
				return m_Name;
			else return std::format("[WARNING]: Layer name not specified!");
		}
	private:
		void QueueTransition(std::unique_ptr<Layer> toLayer);
	protected:
		std::string m_Name;
		std::unordered_set<EventType> m_EventTypesToHandle;
	};
}
