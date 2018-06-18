#pragma once

#include <string>
#include <engine/assets/Asset.hpp>

namespace engine
{
	namespace backend
	{
		struct Archetype : assets::Asset
		{
			std::string prefabName;
			float visionRadius{ 0.f };
			int shootDelay{ 0 };
		};
	}
}
