#pragma once

#include "AssetContainer.h"
#include "AssetIDs.h"

namespace Core
{
	class AssetManager {
	public:
		template<typename Type, typename ID>
		std::expected<std::reference_wrapper<const Type>, AssetLoadError> get(ID id)
		{

		}

		std::expected<void, AssetLoadError> loadNecessary();
		std::expected<void, AssetLoadError> loadAll();
	private:
		// -- Containers ------------
		AssetContainer<sf::Texture, TextureID> m_Textures;
		AssetContainer<sf::Font, TextureID> m_Fonts;
		AssetContainer<sf::SoundBuffer, TextureID> m_Sounds;
	};
}
