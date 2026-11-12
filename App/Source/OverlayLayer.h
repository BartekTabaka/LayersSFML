#pragma once

#include "Core/Layer.h"

#include "Core/Event.h"

class OverlayLayer : public Core::Layer {
public:
	OverlayLayer();

	void onEvent(Core::Event& event) override;
};
