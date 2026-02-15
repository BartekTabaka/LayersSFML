#include "Layer.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <concepts>
#include <set>
#include <vector>
#include <functional>
#include <memory>
#include <print>

struct WindowSpecification		//Window Properties
{
	std::string Title = "Layers SFML";
	uint32_t Width = 1280;
	uint32_t Height = 720;
	uint32_t Style = sf::Style::Default;
};
struct ApplicationSpecification	//Application Properties (Window specification included)
{
	std::string Name = "Application";
	WindowSpecification windowSpec;
};

class Application {
public:
	//Class constructor with default parameters - leave blank for deafult specification or specify name and window specification
	Application(const ApplicationSpecification& appSpec = ApplicationSpecification());
	//Application(const std::string& name, const WindowSpecification& windowSpec = WindowSpecification());

	void Run();
	void Stop();

	//Dodawanie nowej warstwy do aplikacji
	template<std::derived_from<Layer> TLayer>
	void PushLayer() {
		m_LayerStack.push_back(std::make_unique<TLayer>);
	}

	template<std::derived_from<Layer> TLayer>
	TLayer* GetLayer() {
		for (const auto& layer : m_LayerStack) {
			if (auto casted = dynamic_cast<TLayer*>(layer.get())) {
				return casted;
			}
		}
		return nullptr;
	}
private:
	ApplicationSpecification m_Specification;
	std::vector<std::unique_ptr<Layer>> m_LayerStack;
	
};

int main()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML works!", sf::State::Windowed, settings);
	
	sf::Texture texture("assets/Textures/logo.png");
	//sf::Texture texture("C:/dev/LayersSFML/assets/Textures/logo.png");
	sf::Sprite sprite(texture);
	sprite.setOrigin({ texture.getSize().x / 2.f, texture.getSize().y / 2.f });
	sprite.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f - 40 });
	sprite.setScale({ 0.6f, 0.6f });

	sf::Font regularFont("assets/Fonts/LilitaOne-Regular.ttf");
	//sf::Font regularFont("C:/dev/LayersSFML/assets/Fonts/LilitaOne-Regular.ttf");
	sf::Text text(regularFont, "This is a Text", 60);
	text.setOrigin({ text.getLocalBounds().size.x / 2.f, text.getLocalBounds().size.y / 2.f });
	text.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f + 200.f });

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();

		window.draw(sprite);
		window.draw(text);

		window.display();
	}
}

////////////////////////////
//
//	TODO:
//  1. Wyszukiwanie (Application.GetLayer<>();) po nazwie
//
////////////////////////////
