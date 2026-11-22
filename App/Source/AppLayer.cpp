#include "AppLayer.h"

#include <random>
#include <print>
#include <ranges>

#include "Core/Application.h"
#include "Core/InputEvents.h"
#include "Core/Render/Button.h"

AppLayer::AppLayer()
{
	m_Name = "AppLayer";
}

void AppLayer::onEvent(Core::Event& event)
{
	Core::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Core::MouseButtonPressedEvent>([this](Core::MouseButtonPressedEvent& e) { return onMouseButtonPressed(e); });
	dispatcher.dispatch<Core::MouseMovedEvent>([this](Core::MouseMovedEvent& e) { return onMouseMoved(e); });
}

void AppLayer::onAttach()
{
	if (!resetButtonTxt.loadFromFile("Assets/Textures/logo.png")) 
		return;

	const sf::Vector2f windowSize = Core::Application::get().getWindow()->getSize();

	// -- Reset button ------------
	auto resetButton = std::make_unique<Core::Button>("Reset button", resetButtonTxt, [](Core::Button& self) {
		std::println("[ACTION]: {} clicked!", self.getName());
		std::println("[ACTION]: Changing background color to white");
		Core::Application::get().s_ClearColor = sf::Color::White;
	});
	resetButton->setPosition(windowSize / 2.f); // Button class origin is already centered by default
	addObject(std::move(resetButton));
}

void AppLayer::changeBackgroundColor()
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution randomDist(0, 256);

	const auto r = static_cast<uint8_t>(randomDist(generator));
	const auto g = static_cast<uint8_t>(randomDist(generator));
	const auto b = static_cast<uint8_t>(randomDist(generator));
	sf::Color newColor = { r, g, b, 255 };

	Core::Application::get().s_ClearColor = newColor;
}

//
// Event Callbacks
//

bool AppLayer::onMouseButtonPressed(const Core::MouseButtonPressedEvent& event)
{
	if (event.getMouseButton() != 0) return false;

	const auto mousePos = event.getMousePosition();
	for (auto& Object : std::views::reverse(m_Objects)) {
		if (Object->isHit(mousePos)) {
			Object->onClick();
			return true;
		}
	}

	changeBackgroundColor();

	return true;
}
