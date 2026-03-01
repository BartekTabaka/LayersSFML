#include "Core/Application.h"

#include "AppLayer.h"

int main()
{
	/*sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML works!", sf::State::Windowed, settings);*/

	Core::ApplicationSpecification appSpec;
	appSpec.Name = "LayersSFML";
	
	Core::Application application(appSpec);
	application.PushLayer<AppLayer>();   
	application.Run();
	
	/*sf::Texture texture("assets/Textures/logo.png");
	//sf::Texture texture("C:/dev/LayersSFML/App/Assets/Textures/logo.png"); 
	sf::Sprite sprite(texture);
	sprite.setOrigin({ texture.getSize().x / 2.f, texture.getSize().y / 2.f });
	sprite.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f - 40 });
	sprite.setScale({ 0.6f, 0.6f });

	sf::Font regularFont("assets/Fonts/LilitaOne-Regular.ttf");
	//sf::Font regularFont("C:/dev/LayersSFML/App/Assets/Fonts/LilitaOne-Regular.ttf");
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
	}*/
}

////////////////////////////
//
//	TODO:
//  1. Stworzenie w³asnych typów eventów
//  2. Dodanie sprite do AppLayer
//  3. Dodanie OverlayLayer
//  4. Dodanie VoidLayer
//
////////////////////////////
