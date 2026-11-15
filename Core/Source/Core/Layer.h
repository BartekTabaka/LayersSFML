#pragma once

#include <SFML/Graphics.hpp>

#include <format>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "Core/Render/RenderObject.h"
#include "Event.h"
#include "InputEvents.h"

namespace Core 
{
	class Layer {
	public:
		virtual ~Layer() = default;

		virtual void onEvent(Event& event) = 0;

		virtual void onUpdate(float ts);
		virtual void onRender();

		virtual void onAttach() {}
		virtual void onDetach() {}

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
		std::string generateUniqueObjectName(std::string_view repeatedName);
	protected:
		void addObject(std::unique_ptr<RenderObject> obj);
	protected: // Event callbacks
		virtual bool onMouseButtonPressed(const MouseButtonPressedEvent& event);
		virtual bool onMouseMoved(const MouseMovedEvent& event);
	protected:
		// Name of the layer
		std::string m_Name;

		float m_Time = 0.f;

		// Vector of objects of the layer
		std::vector<std::unique_ptr<RenderObject>> m_Objects;
	};
}
