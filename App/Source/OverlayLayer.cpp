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

	auto playButton = std::make_unique<Button>(txt, []() {
		std::println("[ACTION]: Play button clicked!");
		std::println("[ACTION]: Changing background color to white");
		Core::Application::Get().s_ClearColor = sf::Color::White;
	});
	playButton->setPosition({ 500, 250 });
	m_Buttons.push_back(std::move(playButton));
}

void OverlayLayer::OnEvent(Core::Event& event)
{
	if (!m_EventTypesToHandle.contains(event.GetEventType()))
		return;

	Core::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Core::MouseButtonPressedEvent>([this](Core::MouseButtonPressedEvent& e) { return OnMouseButtonPressed(e); });
	dispatcher.Dispatch<Core::MouseMovedEvent>([this](Core::MouseMovedEvent& e) { return OnMouseMoved(e); });
}

void OverlayLayer::OnUpdate(float dT)
{
	m_Time += dT;
}

void OverlayLayer::OnRender()
{
	auto window = Core::Application::Get().GetWindow();
	for (auto& obj : m_Objects) window->Draw(*obj);
	for (auto& btn : m_Buttons) window->Draw(*btn);
}

bool OverlayLayer::OnMouseButtonPressed(Core::MouseButtonPressedEvent& event)
{
	auto mousePos = Core::Application::Get().GetWindow()->GetMousePosWindow();
	for (auto it = m_Buttons.rbegin(); it != m_Buttons.rend(); ++it) {
		if ((*it)->GetGlobalBounds().contains(mousePos)) {
			(*it)->OnClick();
			return true;
		}
	}

	return false;
}

bool OverlayLayer::OnMouseMoved(Core::MouseMovedEvent& event)
{
	auto mousePos = Core::Application::Get().GetWindow()->GetMousePosWindow();
	for (auto& btn : m_Buttons) {
		btn->UpdateHover(mousePos);
	}

	return false;
}

void OverlayLayer::AddObject(std::unique_ptr<RenderObject> obj)
{
	m_Objects.push_back(std::move(obj));
}
