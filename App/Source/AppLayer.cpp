#include "AppLayer.h"

#include <random>

#include "Core/Application.h"

AppLayer::AppLayer()
{
	m_Name = "AppLayer";
}

void AppLayer::onEvent(Core::Event& event)
{
	Core::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Core::MouseButtonPressedEvent>([this](Core::MouseButtonPressedEvent& e) { return onMouseButtonPressed(e); });
}

void AppLayer::onUpdate(float dT)
{
	m_Time += dT;
}

void AppLayer::onRender()
{
}

//
// Event Callbacks
// 

bool AppLayer::onMouseButtonPressed(Core::MouseButtonPressedEvent& event)
{
	if (event.getMouseButton() != 0) return true;

	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution randomDist(0, 256);

	uint8_t r = static_cast<uint8_t>(randomDist(generator));
	uint8_t g = static_cast<uint8_t>(randomDist(generator));
	uint8_t b = static_cast<uint8_t>(randomDist(generator));
	sf::Color newColor = { r, g, b, 255 };

	Core::Application::get().s_ClearColor = newColor;
	return true;
}
