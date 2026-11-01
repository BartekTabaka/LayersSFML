#pragma once

#include <Core/Layer.h>
#include <Core/InputEvents.h>

#include "Rendering/RenderObject.h"

class VoidLayer : public Core::Layer {
public:
	VoidLayer();

	void onEvent(Core::Event& event) override;

	void onUpdate(float ts) override;
	void onRender() override;
private:
	float m_Time = 0.0f;
};