#include "Archetype.hpp"

#include <engine/assets/AssetTypeRegistry.hpp>
#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace assets
	{
		template <>
		serialization::TypeRegistry AssetTypeRegistry<gameplay::Archetype>::value;
	}

	namespace serialization
	{
		template <>
		void serialize<gameplay::Archetype>(gameplay::Archetype &archetype, serialization::Serializer &serializer)
		{
			serializer.declare("shapelist", archetype.shapeListName);
			serializer.declare("vision_radius", archetype.visionRadius);
			serializer.declare("shoot_delay", archetype.shootDelay);
		}
	}
}
