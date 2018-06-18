#pragma once

#include <memory>
#include <engine/backend/ControlContext.hpp>
#include <engine/backend/ControlListener.hpp>
#include <engine/backend/Map.hpp>

namespace engine
{
	namespace assets
	{
		class Manager;
	}

	namespace input
	{
		class Manager;
	}

	namespace backend
	{
		class Listener;

		class Manager : public ControlListener
		{
		public:
			Manager(Listener &listener, assets::Manager &assetsManager, input::Manager &inputManager);

			void update();

			void loadMap(const std::string &mapName);

			// ControlListener
			void characterMoved(Character &character) override;
			void characterSkipped(Character &character) override;
			void gameOver() override;

		private:
			Listener &_listener;

			ControlContext _context;

			std::string _currentMapName;
			std::unique_ptr<Map> _map;
		};
	}
}
