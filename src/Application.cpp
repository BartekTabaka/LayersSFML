#include "Application.h"

// Instancja klasy dostêpna wszêdzie
static Application* s_Appication = nullptr;

Application::Application(const ApplicationSpecification& appSpec)
{
	s_Appication = this;
	
	m_Window = std::make_shared<Window>(m_Specification.windowSpec);
	m_Window->Create();
}

void Application::Run()
{
	m_Running = true;

	while (m_Running) {
		while (m_Window->IsOpen()) {
			// Event handling
			while (const std::optional event = m_Window->pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					m_Window->Destroy();
					Stop();

					break;
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
}

std::shared_ptr<Window> Application::GetWindow() const
{
	return m_Window;
}

Application& Application::Get() {
	assert(s_Appication);
	return *s_Appication;
}
