#pragma once

#include "Core/Layer.h"

#include "Core/InputEvents.h"

class AppLayer : public Core::Layer {
public:
	AppLayer();

	virtual void onEvent(Core::Event& event) override;

	virtual void onUpdate(float dT) override;
	virtual void onRender() override;
private:
	bool onMouseButtonPressed(Core::MouseButtonPressedEvent& event);
private:
	float m_Time = 0.0f;
};