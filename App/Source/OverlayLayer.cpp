#include "OverlayLayer.h"

#include "Core/Application.h"

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

void OverlayLayer::onUpdate(float dT)
{
	m_Time += dT;
}

void OverlayLayer::onRender()
{
	auto window = Core::Application::get().getWindow();
	for (auto& obj : m_Objects) {
		window->draw(*obj);
	}
}

void OverlayLayer::addObject(std::unique_ptr<Core::RenderObject> obj)
{
	m_Objects.push_back(std::move(obj));
}

//
// Event Callbacks
//

bool OverlayLayer::onMouseButtonPressed(Core::MouseButtonPressedEvent& event)
{
	auto mousePos = Core::Application::get().getWindow()->getMousePosWindow();
	for (auto obj = m_Objects.rbegin(); obj != m_Objects.rend(); ++obj) {
		if ((*obj)->isHit(mousePos)) {
			(*obj)->onClick();
			return true;
		}
	}

	return false;
}

bool OverlayLayer::onMouseMoved(Core::MouseMovedEvent& event)
{
	auto mousePos = event.getMousePosition();
	for (auto& obj : m_Objects) {
		obj->updateHover(mousePos);
	}

	return false;
}
