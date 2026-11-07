#pragma once

#include <filesystem>
#include <format>
#include <string>

namespace Core
{
	enum class AssetLoadErrorCode {
		LoadFailed,
		DuplicateID,
		NotFound
	};

	struct AssetLoadError {
		AssetLoadErrorCode code;
		std::filesystem::path path;
		std::string message;
	};
}

template<>
struct std::formatter<Core::AssetLoadError> : std::formatter<std::string> {
	auto format(const Core::AssetLoadError& error, std::format_context& ctx) const
	{
		const std::string prefix = "[AssetLoadError]:";

		// Error code
		std::string code;
		switch (error.code) {
			case Core::AssetLoadErrorCode::LoadFailed:	code = "load failed"; break;
			case Core::AssetLoadErrorCode::DuplicateID:	code = "duplicate ID"; break;
			case Core::AssetLoadErrorCode::NotFound:	code = "not found"; break;
			default: 									code = "unknown error"; break;
		}

		std::string result = std::format("{} {}", prefix, code);

		// File path
		if (!error.path.empty()) {
			result += std::format(" - file path: \"{}\"", error.path.string());
		}

		// Message
		if (!error.message.empty()) {
			result += std::format("\n({})", error.message);
		}
		
		return std::formatter<std::string>::format(result, ctx);
	}
};
