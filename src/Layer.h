#pragma once

#include <SFML/Graphics.hpp>

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void OnUpdate(float ts) {}
	virtual void OnEvent(sf::Event& event) {}
	virtual void OnRender() {}

	template<std::derived_from<Layer> T, typename... Args>
	void TransitionTo(Args&&... args) {

	}
private:

};
