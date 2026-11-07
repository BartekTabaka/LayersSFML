#pragma once

#include <filesystem>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace Core
{
	template<typename Type>
	struct AssetLoader;

	// Texture
	template<>
	struct AssetLoader<sf::Texture> {
		static bool load(sf::Texture& asset, const std::filesystem::path& path)
		{
			return asset.loadFromFile(path);
		}
	};

	// Font
	template<>
	struct AssetLoader<sf::Font> {
		static bool load(sf::Font& asset, const std::filesystem::path& path)
		{
			return asset.openFromFile(path);
		}
	};

	// Sound
	template<>
	struct AssetLoader<sf::SoundBuffer> {
		static bool load(sf::SoundBuffer& asset, const std::filesystem::path& path)
		{
			return asset.loadFromFile(path);
		}
	};

}
