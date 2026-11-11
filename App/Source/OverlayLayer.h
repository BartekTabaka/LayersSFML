#pragma once

#include "Core/Layer.h"

#include <memory>
#include <vector>

#include "Core/InputEvents.h"
#include "Rendering/Button.h"

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
	
	// Temporary texture, here until I create a resource manager
	sf::Texture txt;

	float m_Time = 0.0f;
};