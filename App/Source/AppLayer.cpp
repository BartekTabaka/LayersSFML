#include "AppLayer.h"
#include "Core/Application.h"

#include <random>

AppLayer::AppLayer()
{
	m_Name = "AppLayer";

	m_EventTypesToHandle = {
		Core::EventType::MouseButtonPressed,
		Core::EventType::MouseMoved,
		Core::EventType::WindowClose
	};
}

void AppLayer::OnEvent(Core::Event& event)
{
	if (!m_EventTypesToHandle.contains(event.GetEventType()))
		return;	

	// Logging

	//Dispatching the event
	Core::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Core::MouseButtonPressedEvent>([this](Core::MouseButtonPressedEvent& e) { return OnMouseButtonPressed(e); });
}

void AppLayer::OnUpdate(float dT)
{
	m_Time += dT;
}

void AppLayer::OnRender()
{
}

//
// Event Callbacks
// 

bool AppLayer::OnMouseButtonPressed(Core::MouseButtonPressedEvent& event)
{
	if (event.GetMouseButton() != 0) return true;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 256);

	uint8_t r = dist(gen);
	uint8_t g = dist(gen);
	uint8_t b = dist(gen);
	sf::Color newColor = { r, g, b, 255 };

	Core::Application::Get().s_ClearColor = newColor;
	return true;
}
