#pragma once

#include "Core/Layer.h"
#include "Core/InputEvents.h"

#include <print>

class AppLayer : public Core::Layer {
public:
	AppLayer();

	virtual void OnEvent(Core::Event& event) override;

	virtual void OnUpdate(float dT) override;
	virtual void OnRender() override;
private:
	bool OnMouseButtonPressed(Core::MouseButtonPressedEvent& event);
private:
	float m_Time = 0.0f;
};