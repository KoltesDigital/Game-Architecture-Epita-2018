#pragma once

#include <memory>
#include <string>
#include <vector>
#include <engine/backend/Archetype.hpp>
#include <engine/backend/Character.hpp>
#include <engine/backend/Control.hpp>
#include <engine/backend/Position.hpp>

namespace engine
{
	namespace backend
	{
		struct ControlContext;
		struct MapDescriptor;

		struct Map
		{
			int rows;
			int columns;
			Position target;
			std::vector<std::unique_ptr<Character>> characters;
			Character *playerCharacter;
			std::string nextMap;

			explicit Map(const MapDescriptor &descriptor, ControlContext &context);
		};
	}
}
