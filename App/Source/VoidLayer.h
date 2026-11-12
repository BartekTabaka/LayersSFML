#pragma once

#include "Core/Layer.h"

#include "Core/Event.h"

class VoidLayer : public Core::Layer {
public:
	VoidLayer();

	void onEvent(Core::Event& event) override;
};