#include "AppLayer.h"

#include <random>
#include <print>

#include "Core/Application.h"
#include "Render/Button.h"

AppLayer::AppLayer()
	: resetButtonTxt("Assets/Textures/logo.png")
{
	m_Name = "AppLayer";

	// -- Reset button ------------
	auto resetButton = std::make_unique<Button>("Reset button", resetButtonTxt, []() {
		std::println("[ACTION]: Reset button clicked!");
		std::println("[ACTION]: Changing background color to white");
		Core::Application::get().s_ClearColor = sf::Color::White;
		});
	const sf::Vector2f windowSize = Core::Application::get().getWindow()->getSize();
	resetButton->setPosition({ windowSize.x / 2, windowSize.y / 2 }); // Button class origin is already centered
	addObject(std::move(resetButton));
}

void AppLayer::onEvent(Core::Event& event)
{
	Core::EventDispatcher dispatcher(event);
	dispatcher.dispatch<Core::MouseButtonPressedEvent>([this](Core::MouseButtonPressedEvent& e) { return onMouseButtonPressed(e); });
	dispatcher.dispatch<Core::MouseMovedEvent>([this](Core::MouseMovedEvent& e) { return onMouseMoved(e); });
}

void AppLayer::onUpdate(float dT)
{
	m_Time += dT;
}

void AppLayer::onRender()
{
	auto window = Core::Application::get().getWindow();
	for (auto& obj : m_Objects) {
		window->draw(*obj);
	}
}

void AppLayer::addObject(std::unique_ptr<Core::RenderObject> obj)
{
	m_Objects.push_back(std::move(obj));
}

void AppLayer::changeBackgroundColor()
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution randomDist(0, 256);

	uint8_t r = static_cast<uint8_t>(randomDist(generator));
	uint8_t g = static_cast<uint8_t>(randomDist(generator));
	uint8_t b = static_cast<uint8_t>(randomDist(generator));
	sf::Color newColor = { r, g, b, 255 };

	Core::Application::get().s_ClearColor = newColor;
}

//
// Event Callbacks
//

bool AppLayer::onMouseButtonPressed(Core::MouseButtonPressedEvent& event)
{
	if (event.getMouseButton() != 0) return false;

	auto mousePos = Core::Application::get().getWindow()->getMousePosWindow();
	for (auto obj = m_Objects.rbegin(); obj != m_Objects.rend(); ++obj) {
		if ((*obj)->isHit(mousePos)) {
			(*obj)->onClick();
			return true;
		}
	}

	changeBackgroundColor();

	return true;
}

bool AppLayer::onMouseMoved(Core::MouseMovedEvent& event)
{
	auto mousePos = event.getMousePosition();
	for (auto& obj : m_Objects) {
		obj->updateHover(mousePos);
	}

	return false;
}
