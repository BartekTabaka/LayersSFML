#include "Application.h"

// Instancja klasy dostêpna wszêdzie
static Application* s_Appication = nullptr;

// Zegar który liczy czas dzia³ania aplikacji
static sf::Clock s_RuntimeClock;

Application::Application(const ApplicationSpecification& appSpec)
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
			// Event handling
			while (const std::optional event = m_Window->pollEvent()) {
				if (event->is<sf::Event::Closed>() ||
					event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
					m_Window->Destroy();
					Stop();

					break;
				}
				if (event->is<sf::Event::MouseButtonPressed>() &&
					event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
					std::println("Mouse position in window: {}, {} \nMouse position on screen: {}, {} \nApplication has been running for: {}\n",
						m_Window->GetMousePosWindow().x, m_Window->GetMousePosWindow().y,
						m_Window->GetMousePosScreen().x, m_Window->GetMousePosScreen().y, GetTime());
				}
			}

			m_Window->Clear();

			// Layers render

			m_Window->Display();
		}
	}
}

void Application::Stop()
{
	m_Running = false;
	std::println("Runtime: {}ms ({}s)", s_RuntimeClock.getElapsedTime().asMilliseconds(), GetTime());
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
	switch(unit) {
	case TimeUnit::Seconds:
		return time.asSeconds();
	case TimeUnit::Milliseconds:
		return static_cast<float>(time.asMilliseconds());
	case TimeUnit::Microseconds:
		return static_cast<float>(time.asMicroseconds());
	}

	return 0.f;
}
