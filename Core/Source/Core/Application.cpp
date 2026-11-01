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
		m_Window->create();
	}

	Application::~Application()
	{
		m_Window->destroy();

		s_Appication = nullptr;
	}

	void Application::run()
	{
		m_Running = true;
		s_RuntimeClock.restart();

		float lastTime = s_RuntimeClock.getElapsedTime().asSeconds();

		while (m_Running) {
			while (m_Window->isOpen()) {
				// Event handling
				while (const std::optional event = m_Window->pollEvent()) {
					if (event->is<sf::Event::Closed>() ||
						event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
						m_Window->destroy();
						stop();
						break;
					}
					if (event->is<sf::Event::MouseButtonPressed>()) {
						int pressedButton = static_cast<int>(event->getIf<sf::Event::MouseButtonPressed>()->button);
						MouseButtonPressedEvent event(pressedButton);
						raiseEvent(event);
					}
					if (event->is<sf::Event::MouseMoved>()) {
						sf::Vector2f mousePos = getWindow()->getMousePosWindow();
						MouseMovedEvent event(mousePos);
						raiseEvent(event);
					}
				}

				// DeltaTime
				float currentTime = s_RuntimeClock.getElapsedTime().asSeconds();
				float dT = currentTime - lastTime;
				lastTime = currentTime;

				// Handling Layer transitions before updating and rendering
				handlePendingLayerTransitions();

				// Updating layers
				for (const std::unique_ptr<Layer>& layer : m_LayerStack)
					layer->onUpdate(dT);

				//m_Window->Clear(sf::Color::Cyan);
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
				//This log is for debugging purposes
				std::println("[RaiseEvent] Event \"{}\" has been handled by: {}", event.getName(), layer->getName());
				break;
			}
		}
	}

	std::shared_ptr<Window> Application::getWindow() const
	{
		return m_Window;
	}

	Application& Application::get()
	{
		assert(s_Appication);
		return *s_Appication;
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
					layer = std::move(transition.to);
					break;
				}
			}
		}
		m_PendingTransitions.clear();	
	}
}
