#pragma once

#include "Core/Layer.h"

#include <memory>
#include <vector>

#include "Core/InputEvents.h"
#include "Core/Render/RenderObject.h"

class OverlayLayer : public Core::Layer {
public:
	OverlayLayer();

	virtual void onEvent(Core::Event& event) override;

	virtual void onUpdate(float dT) override;
	virtual void onRender() override;
private:
	void addObject(std::unique_ptr<Core::RenderObject> obj);
private:
	bool onMouseButtonPressed(Core::MouseButtonPressedEvent& event);
	bool onMouseMoved(Core::MouseMovedEvent& event);
private:
	std::vector<std::unique_ptr<Core::RenderObject>> m_Objects;

	float m_Time = 0.0f;
};
