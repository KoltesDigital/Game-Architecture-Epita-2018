#pragma once

#include <map>
#include <memory>
#include <set>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <engine/backend/CharacterId.hpp>
#include <engine/backend/Listener.hpp>
#include <engine/frontend/Entity.hpp>
#include <engine/frontend/EntityContext.hpp>

namespace engine
{
	namespace frontend
	{
		namespace components
		{
			class Player;
		}

		class Manager : public backend::Listener
		{
		public:
			Manager(assets::Manager &assetsManager, graphics::Manager &graphicsManager);

			void setUp();
			void tearDown();

			// backend::Listener
			void onMapLoaded(backend::Map &map) override;
			void onCharacterMoved(const backend::Character &character) override;

			static const float CELL_SIZE;

		private:
			using EntityPtr = std::unique_ptr<Entity>;

			EntityContext _context;

			std::set<EntityPtr> _entities;
			std::map<backend::CharacterId, Entity *> _entityByIds;

			void removeEntities();

			void updateEntityTransform(Entity &entity, const backend::Character &character);
		};
	}
}
