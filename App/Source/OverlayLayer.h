#pragma once

#include "Core/Layer.h"

#include "Core/Event.h"

class OverlayLayer : public Core::Layer {
public:
	OverlayLayer();

	void onEvent(Core::Event& event) override;

	void onAttach() override;
private:
	// Temporary texture, here until I create a resource manager
	sf::Texture debugButtonTexture;
};
