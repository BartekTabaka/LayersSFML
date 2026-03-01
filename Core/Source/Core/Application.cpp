#include "Application.h"
#include "InputEvents.h"

#include <ranges>
#include <print>
namespace Core {

	// Instancja klasy dostêpna wszêdzie (poprzez Application::Get())
	static Application* s_Appication = nullptr;

	// Zegar który liczy czas dzia³ania aplikacji
	static sf::Clock s_RuntimeClock;

	Application::Application(const ApplicationSpecification& appSpec)
		: m_Specification(appSpec)
	{
		s_Appication = this;
		s_RuntimeClock.stop();

		m_Window = std::make_shared<Window>(m_Specification.windowSpec);
		m_Window->Create();
	}

	Application::~Application()
	{
		m_Window->Destroy();

		s_Appication = nullptr;
	}

	void Application::Run()
	{
		m_Running = true;
		s_RuntimeClock.restart();

		while (m_Running) {
			while (m_Window->IsOpen()) {
				// DeltaTime
				float dT = GetDeltaTime();

				// Event handling
				while (const std::optional event = m_Window->pollEvent()) {
					if (event->is<sf::Event::Closed>() ||
						event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
						m_Window->Destroy();
						Stop();
						break;
					}
					if (event->is<sf::Event::MouseButtonPressed>()) {
						int pressedButton = static_cast<int>(event->getIf<sf::Event::MouseButtonPressed>()->button);
						MouseButtonPressedEvent event(pressedButton);
						RaiseEvent(event);
					}
				}

				// Handling Layer transitions before updating and rendering
				HandlePendingLayerTransitions();

				// Updating layers
				for (const std::unique_ptr<Layer>& layer : m_LayerStack)
					layer->OnUpdate(dT);

				//m_Window->Clear(sf::Color::Cyan);
				m_Window->Clear(s_ClearColor);

				// Rendering layers
				for (const std::unique_ptr<Layer>& layer : m_LayerStack)
					layer->OnRender();

				m_Window->Display();
			}
		}
	}

	void Application::Stop()
	{
		m_Running = false;
		std::println("Runtime: {}ms ({}s)", s_RuntimeClock.getElapsedTime().asMilliseconds(), GetTime());
	}

	void Application::RaiseEvent(Event& event)
	{
		for (auto& layer : std::views::reverse(m_LayerStack)) {
			layer->OnEvent(event);
			if (event.Handled) {
				//This log is for debugging purposes
				std::println("[RaiseEvent] Event \"{}\" has been handled by: {}", event.GetName(), layer->GetName());
				break;
			}
		}
	}

	std::shared_ptr<Window> Application::GetWindow() const
	{
		return m_Window;
	}

	Application& Application::Get()
	{
		assert(s_Appication);
		return *s_Appication;
	}

	float Application::GetTime(TimeUnit unit)
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

	float Application::GetDeltaTime()
	{
		return s_RuntimeClock.restart().asSeconds();
	}

	void Application::QueueLayerTransition(Layer* from, std::unique_ptr<Layer> to)
	{
		m_PendingTransitions.push_back({ from, std::move(to) });
	}

	void Application::HandlePendingLayerTransitions()
	{
		for (auto& transition : m_PendingTransitions) {
			for (auto& layer : m_LayerStack) {
				std::println("{}", layer->GetName());
				if (layer.get() == transition.from) {
					layer = std::move(transition.to);
					break;
				}
			}
		}
		m_PendingTransitions.clear();	
	}
}
