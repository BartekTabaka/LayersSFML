#include "OverlayLayer.h"
#include "Core/Application.h"
#include <print>
OverlayLayer::OverlayLayer()
	: txt1("Assets/Textures/logo.png"),
	  sp1(txt1)
{
	m_Name = "OverlayLayer";

	m_EventTypesToHandle = {
		Core::EventType::MouseButtonPressed
	};

	sp1.setPosition({ 500, 250 });
}

void OverlayLayer::OnEvent(Core::Event& event)
{
	if (!m_EventTypesToHandle.contains(event.GetEventType()))
		return;

	Core::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Core::MouseButtonPressedEvent>([this](Core::MouseButtonPressedEvent& e) { return OnMouseButtonPressed(e); });
}

void OverlayLayer::OnUpdate(float dT)
{
	m_Time += dT;
}

void OverlayLayer::OnRender()
{
	Core::Application::Get().GetWindow()->Draw(sp1);
}

bool OverlayLayer::OnMouseButtonPressed(Core::MouseButtonPressedEvent& event)
{
	if (!IsButtonHovered()) return false;

	return true;
}

bool OverlayLayer::IsButtonHovered()
{
	using Vec2f = sf::Vector2f;
	Vec2f mousePos = Core::Application::Get().GetWindow()->GetMousePosWindow();

	bool hovered = false;

	return hovered;
}
