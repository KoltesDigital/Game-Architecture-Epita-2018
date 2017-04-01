#pragma once

#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>

namespace engine
{
	namespace gameplay
	{
		class Entity;

		namespace entities
		{
			class Player;
		}

		class Manager
		{
		public:
			void update();
			void draw();

			void gameOver();

			sf::Vector2f getViewCenter() const;

			void loadMap(const std::string &mapName);
			void loadNextMap();

			const entities::Player &getPlayer() const;

			static const float CELL_SIZE;

			static Manager &getInstance();

		private:
			std::set<Entity *> entities;
			entities::Player *playerEntity{};

			// Map
			std::string currentMapName;
			std::string nextMapName;
			int rows{ 0 };
			int columns{ 0 };

			bool preventMapCompletion{ false };
			bool nextMapRequested{ false };

			static Manager *instance;
		};
	}
}
