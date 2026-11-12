#include "OverlayLayer.h"

#include "Core/InputEvents.h"

OverlayLayer::OverlayLayer()
{
	m_Name = "OverlayLayer";
}

void OverlayLayer::onEvent(Core::Event& event)
{
	Core::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Core::MouseButtonPressedEvent>([this](Core::MouseButtonPressedEvent& e) { return onMouseButtonPressed(e); });
	dispatcher.dispatch<Core::MouseMovedEvent>([this](Core::MouseMovedEvent& e) { return onMouseMoved(e); });
}
