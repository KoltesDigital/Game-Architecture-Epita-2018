#include "Archetype.hpp"

#include <engine/assets/AssetTypeRegistry.hpp>
#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace assets
	{
		template <>
		serialization::TypeRegistry AssetTypeRegistry<backend::Archetype>::value;
	}

	namespace serialization
	{
		template <>
		void serialize<backend::Archetype>(backend::Archetype &archetype, serialization::Serializer &serializer)
		{
			serializer.declare("prefab", archetype.prefabName);
			serializer.declare("vision_radius", archetype.visionRadius);
			serializer.declare("shoot_delay", archetype.shootDelay);
		}
	}
}
