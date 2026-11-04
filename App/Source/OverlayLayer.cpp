#include "OverlayLayer.h"
#include "Core/Application.h"

OverlayLayer::OverlayLayer()
	: txt("Assets/Textures/logo.png")
{
	m_Name = "OverlayLayer";

	m_EventTypesToHandle = {
		Core::EventType::MouseButtonPressed,
		Core::EventType::MouseMoved
	};

	// -- Reset button ------------
	auto resetButton = std::make_unique<Button>(txt, []() {
		std::println("[ACTION]: Play button clicked!");
		std::println("[ACTION]: Changing background color to white");
		Core::Application::get().s_ClearColor = sf::Color::White;
	});
	const sf::Vector2f windowSize = Core::Application::get().getWindow()->getSize();
	resetButton->setPosition({ windowSize.x / 2, windowSize.y / 2 }); // Button class origin is already centered
	m_Buttons.push_back(std::move(resetButton));
}

void OverlayLayer::onEvent(Core::Event& event)
{
	if (!m_EventTypesToHandle.contains(event.getEventType()))
		return;

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
	for (auto& obj : m_Objects) window->draw(*obj);
	for (auto& btn : m_Buttons) window->draw(*btn);
}

bool OverlayLayer::onMouseButtonPressed(Core::MouseButtonPressedEvent& event)
{
	auto mousePos = Core::Application::get().getWindow()->getMousePosWindow();
	for (auto it = m_Buttons.rbegin(); it != m_Buttons.rend(); ++it) {
		if ((*it)->isHit(mousePos)) {
			(*it)->onClick();
			return true;
		}
	}

	return false;
}

bool OverlayLayer::onMouseMoved(Core::MouseMovedEvent& event)
{
	auto mousePos = Core::Application::get().getWindow()->getMousePosWindow();
	for (auto& btn : m_Buttons) {
		btn->updateHover(mousePos);
	}

	return false;
}

void OverlayLayer::addObject(std::unique_ptr<RenderObject> obj)
{
	m_Objects.push_back(std::move(obj));
}
