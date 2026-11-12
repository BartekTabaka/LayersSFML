#pragma once

#include "Core/Layer.h"

#include "Core/Event.h"

class AppLayer : public Core::Layer {
public:
	AppLayer();

	void onEvent(Core::Event& event) override;
private:
	void changeBackgroundColor();
private: // Event callbacks
	bool onMouseButtonPressed(Core::MouseButtonPressedEvent& event) override;
private:
	// Temporary texture, here until I create a resource manager
	sf::Texture resetButtonTxt;
};
