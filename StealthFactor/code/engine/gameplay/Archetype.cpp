#include "Archetype.hpp"

#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace gameplay
	{
		void Archetype::serialize(serialization::Serializer & serializer)
		{
			serializer.declare("shapelist", shapeListName);
			serializer.declare("vision_radius", visionRadius);
			serializer.declare("shoot_delay", shootDelay);
		}
	}
}
