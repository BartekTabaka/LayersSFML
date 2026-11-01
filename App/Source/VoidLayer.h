#pragma once

#include <Core/Layer.h>
#include <Core/InputEvents.h>

#include "Rendering/RenderObject.h"

class VoidLayer : public Core::Layer {
public:
	VoidLayer();

	void OnEvent(Core::Event& event) override;
	void OnUpdate(float ts) override;
	void OnRender() override;
private:
	float m_Time = 0.0f;
};