#pragma once

#include <filesystem>
#include <memory>
#include <unordered_map>
#include <expected>
#include <functional>
#include <utility>

#include "AssetLoader.h"
#include "AssetLoadError.h"

// Type - type of assets to store
// ID - enum type used to identify individual assets
template<typename Type, typename ID>
class AssetContainer {
public:
	using Result = std::expected<std::reference_wrapper<const Type>, AssetLoadError>;

	Result load(ID id, const std::filesystem::path& path)
	{
		const auto normalizedPath = path.lexically_normal();

		// Check if we already store an asset with this ID
		if (auto it = m_Assets.find(id); it != m_Assets.end()) {
			// Same ID, same path - no need to load the asset again
			if (it->second.path == path)
				return std::cref(*it->second.asset);

			// Same ID, but different paths - return error
			return std::unexpected(AssetLoadError{
				AssetLoadErrorCode::DuplicateID,
				normalizedPath,
				"Asset ID is already registered with a different path"
			});
		}

		// Try to load the asset
		auto asset = std::make_unique<Type>();
		if (!AssetLoader<Type>::load(*asset, normalizedPath)) {
			return std::unexpected(AssetLoadError{
				AssetLoadErrorCode::LoadFailed,
				normalizedPath,
				"Failed to load asset"
			});
		}

		// Emplace to container and return the asset
		auto [it, inserted] = m_Assets.emplace(id, Entry {
			std::move(asset),
			normalizedPath
		});
		return std::cref(*it->second.asset);
	}

	Result get(ID id) const
	{
		auto it = m_Assets.find(id);
		if (it == m_Assets.end()) {
			return std::unexpected(AssetLoadError{
				AssetLoadErrorCode::NotFound,
				{},
				"Asset ID was not found in cache"
			});
		}

		return std::cref(*it->second.asset);
	}

	bool contains(ID id) const noexcept
	{
		return m_Assets.contains(id);
	}

	void clear() noexcept
	{
		m_Assets.clear();
	}
private:
	struct Entry {
		std::unique_ptr<Type> asset;
		std::filesystem::path path;
	};
	std::unordered_map<ID, Entry> m_Assets;
};
