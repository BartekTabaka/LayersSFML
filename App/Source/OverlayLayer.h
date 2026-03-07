#pragma once

#include <vector>

#include "Core/Layer.h"
#include "Core/InputEvents.h"

#include "Rendering/RenderObject.h"

class OverlayLayer : public Core::Layer {
public:
	OverlayLayer();

	virtual void OnEvent(Core::Event& event) override;
	
	virtual void OnUpdate(float dT) override;
	virtual void OnRender() override;
private:
	bool OnMouseButtonPressed(Core::MouseButtonPressedEvent& event);
private:
	bool IsButtonHovered();
private:
	sf::Texture txt1;
	sf::Sprite sp1;

	float m_Time = 0.0f;
};