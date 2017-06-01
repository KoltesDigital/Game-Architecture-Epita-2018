#pragma once

#include <string>

namespace engine
{
	namespace serialization
	{
		class Serializer;
	}

	namespace gameplay
	{
		struct Archetype
		{
			std::string shapeListName;
			float visionRadius{ 0.f };
			int shootDelay{ 0 };

			void serialize(serialization::Serializer &serializer);
		};
	}
}
