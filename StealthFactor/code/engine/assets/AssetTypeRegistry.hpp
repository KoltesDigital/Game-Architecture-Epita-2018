#pragma once

#include <engine/serialization/TypeRegistry.h>

namespace engine
{
	namespace assets
	{
		template <typename T>
		struct AssetTypeRegistry
		{
			static serialization::TypeRegistry value;
		};
	}
}
