#include "Application.h"

#include <print>
#include <ranges>

namespace Core {

	// Instance of the class accessible globally (via Application::Get())
	static Application* s_Application = nullptr;

	// Timer that tracks the application's runtime
	static sf::Clock s_RuntimeClock;

	Application::Application(const ApplicationSpecification& appSpec)
		: m_Specification(appSpec)
	{
		s_Application = this;
		s_RuntimeClock.stop();

		m_Window = std::make_shared<Window>(m_Specification.windowSpec);
		m_Window->create();
	}

	Application::~Application()
	{
		m_Window->destroy();

		s_Application = nullptr;
	}

	void Application::run()
	{
		m_Running = true;
		s_RuntimeClock.restart();

		float lastTime = s_RuntimeClock.getElapsedTime().asSeconds();

		while (m_Running) {
			while (m_Window->isOpen()) {
				// Event handling
				m_Window->processEvents();

				// DeltaTime
				float currentTime = s_RuntimeClock.getElapsedTime().asSeconds();
				float dT = currentTime - lastTime;
				lastTime = currentTime;

				// NOTE: Handling Layer transitions before updating and rendering
				handlePendingLayerTransitions();

				// Updating layers
				for (const std::unique_ptr<Layer>& layer : m_LayerStack)
					layer->onUpdate(dT);

				m_Window->clear(s_ClearColor);

				// Rendering layers
				for (const std::unique_ptr<Layer>& layer : m_LayerStack)
					layer->onRender();

				m_Window->display();
			}
		}
	}

	void Application::stop()
	{
		m_Running = false;
		std::println("Runtime: {}ms ({}s)", s_RuntimeClock.getElapsedTime().asMilliseconds(), getTime());
	}

	void Application::raiseEvent(Event& event)
	{
		for (auto& layer : std::views::reverse(m_LayerStack)) {
			layer->onEvent(event);
			if (event.handled) {
				std::println("[RaiseEvent] Event \"{}\" has been handled by: {}", event.getName(), layer->getName());
				break;
			}
		}

		if (event.is(EventType::WindowClose)) {
			m_Window->destroy();
			stop();
		}
	}

	Application& Application::get()
	{
		assert(s_Application);
		return *s_Application;
	}

	float Application::getTime(TimeUnit unit)
	{
		auto time = s_RuntimeClock.getElapsedTime();
		switch (unit) {
		case TimeUnit::Seconds:
			return time.asSeconds();
		case TimeUnit::Milliseconds:
			return static_cast<float>(time.asMilliseconds());
		case TimeUnit::Microseconds:
			return static_cast<float>(time.asMicroseconds());
		}

		return 0.f;
	}

	void Application::queueLayerTransition(Layer* from, std::unique_ptr<Layer> to)
	{
		m_PendingTransitions.push_back({ from, std::move(to) });
	}

	void Application::handlePendingLayerTransitions()
	{
		for (auto& transition : m_PendingTransitions) {
			for (auto& layer : m_LayerStack) {
				std::println("{}", layer->getName());
				if (layer.get() == transition.from) {
					transition.from->onDetach();

					layer = std::move(transition.to);
					layer->onAttach();

					break;
				}
			}
		}
		m_PendingTransitions.clear();	
	}
}
