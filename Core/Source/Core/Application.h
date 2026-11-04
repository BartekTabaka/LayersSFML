#pragma once

#include "Layer.h"
#include "Window.h"
#include "Event.h"

#include <memory>
#include <concepts>
#include <string>
#include <vector>
#include <print>

namespace Core 
{
	enum class TimeUnit {
		Seconds, Milliseconds, Microseconds
	};

	struct ApplicationSpecification { // Application properties (Window specification included)
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

		//Dodawanie nowej warstwy
		template<std::derived_from<Layer> TLayer>
		void pushLayer()
		{
			m_LayerStack.push_back(std::make_unique<TLayer>());
		}

		//Wydobycie/otrzymanie warstwy z m_LayerStack
		template<std::derived_from<Layer> TLayer>
		TLayer* getLayer()
		{
			// Iteracja przez każdą warstwę w m_LayerStack
			for (const auto& layer : m_LayerStack) {
				if (auto casted = dynamic_cast<TLayer*>(layer.get())) { // Rzutujemy każdą warstwę na oczekiwany typ 
					// (TLayer) i sprawdzamy czy taka jest, jeśli:
					// tak - zwracamy pierwszą którą udało się rzutować,
					// nie - zwracamy nullptr (informacja że nie ma 
					//		 warstwy o podanym typie
					return casted;
				}
			}
			return nullptr;
		}

		std::shared_ptr<Window> getWindow() const; // Returns a pointer to window instance

		static Application& get(); //Get Instance
		static float getTime(TimeUnit unit = TimeUnit::Seconds); // Get application runtime

		// Chwilowa zmienna, żeby nadać jakąś funkcję klikaniu myszy
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
