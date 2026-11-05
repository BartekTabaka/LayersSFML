#pragma once

#include <concepts>
#include <memory>
#include <print>
#include <string>
#include <vector>

#include "Event.h"
#include "Layer.h"
#include "Window.h"
#include "Asset/AssetManager.h"

namespace Core 
{
	enum class TimeUnit {
		Seconds, Milliseconds, Microseconds
	};

	// Application properties (Window specification included)
	struct ApplicationSpecification {
		std::string Name = "Application";
		WindowSpecification windowSpec;
	};

	class Application {
		struct PendingTransition {
			Layer* from;
			std::unique_ptr<Layer> to;
		};
		std::vector<PendingTransition> m_PendingTransitions;
	public:
		// Class constructor with default parameters - leave blank for deafult specification or 
		// specify name and window specification
		Application(const ApplicationSpecification& appSpec = ApplicationSpecification());
		~Application();

		void run();
		void stop();

		void raiseEvent(Event& event); // layer->OnEvent(event);

		// Add new layer
		template<std::derived_from<Layer> TLayer>
		void pushLayer()
		{
			m_LayerStack.push_back(std::make_unique<TLayer>());
		}

		// Get layer from m_LayerStack
		template<std::derived_from<Layer> TLayer>
		TLayer* getLayer()
		{
			// Iterate through every layer in m_LayerStack
			for (const auto& layer : m_LayerStack) {
				// Cast each layer to the expected type (TLayer) and check if the cast succeeds
				if (auto casted = dynamic_cast<TLayer*>(layer.get())) {
					/* If successful, return the first matching layer.
					   If unsuccessful, return nullptr (indicating that no layer of the specified type was found). */
					return casted;
				}
			}
			return nullptr;
		}

		std::shared_ptr<Window> getWindow() const; // Returns a pointer to window instance

		static Application& get(); // Get Instance
		static float getTime(TimeUnit unit = TimeUnit::Seconds); // Get application runtime

		// Temporary variable
		sf::Color s_ClearColor = sf::Color::Cyan;
	private:
		void queueLayerTransition(Layer* from, std::unique_ptr<Layer> to);
		void handlePendingLayerTransitions();
	private:
		bool m_Running = false;

		ApplicationSpecification m_Specification;

		std::vector<std::unique_ptr<Layer>> m_LayerStack;

		std::shared_ptr<Window> m_Window;

		friend class Layer;
	};
}
