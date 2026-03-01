#include "AppLayer.h"
#include "Core/Application.h"
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
	Core::Application::Get().s_ClearColor = sf::Color::Red;
	return true;
}
