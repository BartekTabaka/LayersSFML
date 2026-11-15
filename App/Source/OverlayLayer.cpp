#include "OverlayLayer.h"

#include "Core/InputEvents.h"
#include "Core/Render/Button.h"

OverlayLayer::OverlayLayer()
	: debugButtonTexture("Assets/Textures/button_blue.png")
{
	m_Name = "OverlayLayer";

	// -- Show Debug button ------------
	auto showDebugButton = std::make_unique<Core::Button>("Show debug button", debugButtonTexture, [](Core::Button& self) {
		self.s_DebugHitboxes = !self.s_DebugHitboxes;
	});
	showDebugButton->setBaseScale({ 0.4f, 0.4f });
	showDebugButton->setPosition({ 150.f, 100.f });
	addObject(std::move(showDebugButton));
}

void OverlayLayer::onEvent(Core::Event& event)
{
	Core::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Core::MouseButtonPressedEvent>([this](Core::MouseButtonPressedEvent& e) { return onMouseButtonPressed(e); });
	dispatcher.dispatch<Core::MouseMovedEvent>([this](Core::MouseMovedEvent& e) { return onMouseMoved(e); });
}

///////////
//
// TODO: dodaj auto-origin jako parametr:
// true -> wyśrodkowany origin
// false -> oryginalny origin
// LUB
// enum class OriginMode { TopLeft, Center }; 
// + OriginMode jako parametr
//
///////////
