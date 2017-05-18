#pragma once

#include <functional>
#include <vector>

namespace engine
{
	namespace gameplay
	{
		class Entity;
	}

	namespace physics
	{
		//using EntitySet = std::vector<std::reference_wrapper<const gameplay::Entity>>;
		using EntitySet = std::vector<const gameplay::Entity *>;
	}
}
