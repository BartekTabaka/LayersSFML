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

void AppLayer::onEvent(Core::Event& event)
{
	if (!m_EventTypesToHandle.contains(event.getEventType()))
		return;	

	// Logging

	//Dispatching the event
	Core::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Core::MouseButtonPressedEvent>([this](Core::MouseButtonPressedEvent& e) { return onMouseButtonPressed(e); });
}

void AppLayer::onUpdate(float dT)
{
	m_Time += dT;
}

void AppLayer::onRender()
{
}

//
// Event Callbacks
// 

bool AppLayer::onMouseButtonPressed(Core::MouseButtonPressedEvent& event)
{
	if (event.getMouseButton() != 0) return true;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 256);

	uint8_t r = static_cast<uint8_t>(dist(gen));
	uint8_t g = static_cast<uint8_t>(dist(gen));
	uint8_t b = static_cast<uint8_t>(dist(gen));
	sf::Color newColor = { r, g, b, 255 };

	Core::Application::get().s_ClearColor = newColor;
	return true;
}
