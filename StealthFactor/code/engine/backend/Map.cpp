#include "Map.hpp"

#include <engine/backend/MapDescriptor.hpp>
#include <engine/backend/controls/Enemy.hpp>
#include <engine/backend/controls/Player.hpp>

namespace engine
{
	namespace backend
	{
		Map::Map(const MapDescriptor &descriptor, ControlContext &context)
			: rows{ descriptor.rows }
			, columns{ descriptor.columns }
			, target{ descriptor.target.position }
			, nextMap{ descriptor.nextMap }
		{
			playerCharacter = new Character;
			playerCharacter->position = descriptor.player.position;
			playerCharacter->control.reset(new controls::Player{ *playerCharacter, context });
			characters.emplace_back(playerCharacter);

			for (auto &enemyDescriptor : descriptor.enemies)
			{
				auto enemyCharacter{ new Character };
				enemyCharacter->position = enemyDescriptor.position;
				enemyCharacter->control.reset(new controls::Enemy{ *enemyCharacter, context, enemyDescriptor, *playerCharacter });
				characters.emplace_back(enemyCharacter);
			}
		}
	}
}
