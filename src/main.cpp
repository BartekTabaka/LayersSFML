#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "SFML works!");
    
    sf::Texture texture("assets/Textures/logo.png");
    sf::Sprite sprite(texture);
	sprite.setOrigin({ texture.getSize().x / 2.f, texture.getSize().y / 2.f });
    sprite.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f - 40 });
	sprite.setScale({ 0.6f, 0.6f });

	sf::Font regularFont("assets/Fonts/LilitaOne-Regular.ttf");
    sf::Text text(regularFont, "This is a Text");
	text.setCharacterSize(60);
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