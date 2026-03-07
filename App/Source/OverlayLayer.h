#pragma once

#include <vector>
#include <memory>

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
	bool OnMouseMoved(Core::MouseMovedEvent& event);
private:
	bool IsButtonHovered();
	RenderObject* GetHoveredObject();
	void AddObject(std::unique_ptr<RenderObject> obj);
private:

	std::vector<std::unique_ptr<RenderObject>> m_Objects;
	std::vector<std::unique_ptr<Button>> m_Buttons;
	
	// Temporary texture, here until I create a resource manager
	sf::Texture txt;

	float m_Time = 0.0f;
};