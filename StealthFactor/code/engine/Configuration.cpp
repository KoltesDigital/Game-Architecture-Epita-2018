#include "Configuration.hpp"

#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace serialization
	{
		template <>
		void serialize<Configuration>(Configuration &configuration, serialization::Serializer &serializer)
		{
			serializer.declare("start_map", configuration.startMap);
		}
	}
}
