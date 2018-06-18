#pragma once

#include <string>
#include <engine/assets/Asset.hpp>

namespace engine
{
	namespace gameplay
	{
		struct Archetype : assets::Asset
		{
			std::string shapeListName;
			float visionRadius{ 0.f };
			int shootDelay{ 0 };
		};
	}
}
