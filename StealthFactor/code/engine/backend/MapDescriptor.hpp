#pragma once

#include <string>
#include <vector>
#include <engine/assets/Asset.hpp>
#include <engine/backend/Position.hpp>

namespace engine
{
	namespace backend
	{
		struct HasPositionDescriptor
		{
			Position position;
		};

		struct TargetDescriptor : HasPositionDescriptor
		{
		};

		struct PlayerDescriptor : HasPositionDescriptor
		{
		};

		struct EnemyDescriptor : HasPositionDescriptor
		{
			std::string archetypeName;
		};

		struct MapDescriptor : assets::Asset
		{
			int rows;
			int columns;
			TargetDescriptor target;
			PlayerDescriptor player;
			std::vector<EnemyDescriptor> enemies;
			std::string nextMap;
		};
	}
}
