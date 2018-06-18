#include "BackendManager.hpp"

#include <iostream>
#include <engine/assets/AssetsManager.hpp>
#include <engine/backend/Listener.hpp>
#include <engine/backend/MapDescriptor.hpp>

namespace engine
{
	namespace backend
	{
		Manager::Manager(Listener &listener, assets::Manager &assetsManager, input::Manager &inputManager)
			: _listener{ listener }
			, _context{ assetsManager, inputManager, *this }
		{
		}

		void Manager::update()
		{
			for (auto &character : _map->characters)
			{
				character->control->update();
			}

			if (_map->playerCharacter->position == _map->target)
			{
				loadMap(_map->nextMap);
			}
		}

		void Manager::loadMap(const std::string &mapName)
		{
			auto mapDescriptor{ _context.assetsManager.getAsset<MapDescriptor>(mapName) };
			if (!mapDescriptor)
			{
				std::cerr << "Map " << mapName << " failed to load.";
				return;
			}

			_currentMapName = mapName;
			_map.reset(new Map{ *mapDescriptor, _context });

			_listener.onMapLoaded(*_map);
		}

		void Manager::characterMoved(Character &character)
		{
			_listener.onCharacterMoved(character);
		}

		void Manager::characterSkipped(Character &)
		{
		}

		void Manager::gameOver()
		{
			std::cout << "Game over" << std::endl;
			loadMap(_currentMapName);
		}
	}
}
