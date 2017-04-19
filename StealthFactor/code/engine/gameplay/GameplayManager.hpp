#pragma once

#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <engine/graphics/ViewProvider.hpp>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/EntityListener.hpp>

namespace engine
{
	namespace gameplay
	{
		class Entity;

		namespace entities
		{
			class Player;
		}

		class Manager : public graphics::ViewProvider, public EntityListener
		{
		public:
			Manager(graphics::Manager &graphicsManager, input::Manager &inputManager, physics::Manager &physicsManager);

			void update();
			void draw();

			void loadMap(const std::string &mapName);

			// EntityListener
			void gameOver() override;
			void loadNextMap() override;
			const entities::Player &getPlayer() const override;

			// ViewProvider
			sf::Vector2f getViewCenter() const override;

			static const float CELL_SIZE;

		private:
			EntityContext context;

			std::set<Entity *> entities;
			entities::Player *playerEntity{};

			// Map
			std::string currentMapName;
			std::string nextMapName;
			int rows{ 0 };
			int columns{ 0 };

			bool preventMapCompletion{ false };
			bool nextMapRequested{ false };
		};
	}
}
