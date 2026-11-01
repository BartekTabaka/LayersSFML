#pragma once

#include <vector>
#include <memory>

#include "Core/Layer.h"
#include "Core/InputEvents.h"

#include "Rendering/RenderObject.h"

class OverlayLayer : public Core::Layer {
public:
	OverlayLayer();

	virtual void onEvent(Core::Event& event) override;
	
	virtual void onUpdate(float dT) override;
	virtual void onRender() override;
private:
	bool onMouseButtonPressed(Core::MouseButtonPressedEvent& event);
	bool onMouseMoved(Core::MouseMovedEvent& event);
private:
	void addObject(std::unique_ptr<RenderObject> obj);
private:

	std::vector<std::unique_ptr<RenderObject>> m_Objects;
	std::vector<std::unique_ptr<Button>> m_Buttons;
	
	// Temporary texture, here until I create a resource manager
	sf::Texture txt;

	float m_Time = 0.0f;
};