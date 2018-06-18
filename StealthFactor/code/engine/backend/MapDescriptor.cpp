#include "MapDescriptor.hpp"

#include <engine/assets/AssetTypeRegistry.hpp>
#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace assets
	{
		template <>
		serialization::TypeRegistry AssetTypeRegistry<backend::MapDescriptor>::value;
	}

	namespace serialization
	{
		template <>
		void serialize<backend::HasPositionDescriptor>(backend::HasPositionDescriptor &descriptor, serialization::Serializer &serializer)
		{
			serializer.declare("row", descriptor.position.row);
			serializer.declare("column", descriptor.position.column);
		}

		template <>
		void serialize<backend::TargetDescriptor>(backend::TargetDescriptor &descriptor, serialization::Serializer &serializer)
		{
			serialize(static_cast<backend::HasPositionDescriptor &>(descriptor), serializer);
		}

		template <>
		void serialize<backend::PlayerDescriptor>(backend::PlayerDescriptor &descriptor, serialization::Serializer &serializer)
		{
			serialize(static_cast<backend::HasPositionDescriptor &>(descriptor), serializer);
		}

		template <>
		void serialize<backend::EnemyDescriptor>(backend::EnemyDescriptor &descriptor, serialization::Serializer &serializer)
		{
			serialize(static_cast<backend::HasPositionDescriptor &>(descriptor), serializer);
			serializer.declare("archetype", descriptor.archetypeName);
		}

		template <>
		void serialize<backend::MapDescriptor>(backend::MapDescriptor &descriptor, serialization::Serializer &serializer)
		{
			serializer.declare("rows", descriptor.rows);
			serializer.declare("columns", descriptor.columns);
			serializer.declare("target", descriptor.target);
			serializer.declare("player", descriptor.player);
			serializer.declare("enemies", descriptor.enemies);
			serializer.declare("next_map", descriptor.nextMap);
		}
	}
}
