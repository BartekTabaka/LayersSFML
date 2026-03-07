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

	/*auto sprite = std::make_unique<MySprite>(txt);
	sprite->setScale({ 0.5f, 0.5f });

	m_Objects.push_back(std::move(sprite));*/

	//// Play button
	//auto playBtn = std::make_unique<Button>(txt, []() {
	//	std::println("Play!");
	//});
	//m_Objects.push_back(std::move(playBtn));

	//// Options button
	//auto optBtn = std::make_unique<Button>(txt, []() {
	//	std::println("Options!");
	//});
	//optBtn->setPosition({ 600, 200 });
	//m_Objects.push_back(std::move(optBtn));

	auto playButton = std::make_unique<Button>(txt, []() {
		std::println("Play button clicked!");
	});
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
	for (auto& obj : m_Objects) {
		window->Draw(*obj);
	}
	for (auto& btn : m_Buttons) {
		window->Draw(*btn);
	}
}

bool OverlayLayer::OnMouseButtonPressed(Core::MouseButtonPressedEvent& event)
{
	if (IsButtonHovered()) {
		for (auto& btn : m_Buttons) {
			btn->OnClick();
		}
	}

	return true;
}

bool OverlayLayer::OnMouseMoved(Core::MouseMovedEvent& event)
{
	IsButtonHovered();

	return false;
}

bool OverlayLayer::IsButtonHovered()
{
	for (auto& btn : m_Buttons) {
		if (btn->IsHovered()) {
			btn->OnHover();
			return true;
		}
	}
	return false;
}

RenderObject* OverlayLayer::GetHoveredObject()
{
	auto mousePos = Core::Application::Get().GetWindow()->GetMousePosWindow();
	for (auto it = m_Objects.rbegin(); it != m_Objects.rend(); ++it) {
		if ((*it)->GetGlobalBounds().contains(mousePos)) {
			return it->get();
		}
	}

	return nullptr;
}

void OverlayLayer::AddObject(std::unique_ptr<RenderObject> obj)
{
	m_Objects.push_back(std::move(obj));
}
