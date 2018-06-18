#include "FrontendManager.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <engine/backend/Map.hpp>
#include <engine/assets/AssetsManager.hpp>
#include <engine/frontend/Prefab.hpp>
#include <engine/frontend/components/Camera.hpp>
#include <engine/frontend/components/Transform.hpp>

namespace engine
{
	namespace frontend
	{
		const float Manager::CELL_SIZE = 50.f;

		Manager::Manager(assets::Manager &assetsManager, graphics::Manager &graphicsManager)
			: _context{ assetsManager, graphicsManager }
		{
		}

		void Manager::setUp()
		{
		}

		void Manager::tearDown()
		{
			removeEntities();
		}

		void Manager::onMapLoaded(backend::Map &map)
		{
			removeEntities();

			for (auto &character : map.characters)
			{
				std::string prefabName = character->control->getPrefabName();
				auto prefab{ _context.assetsManager.getAsset<Prefab>(prefabName) };
				if (!prefab)
				{
					std::cerr << "Prefab [" << prefabName << "] does not exist." << std::endl;
					continue;
				}

				auto entity{ prefab->instantiate(_context) };
				if (!entity)
				{
					std::cerr << "Prefab [" << prefabName << "] instantiated no entity." << std::endl;
					continue;
				}

				updateEntityTransform(*entity, *character);

				_entityByIds.insert(std::make_pair(character->id, entity.get()));
				_entities.insert(std::move(entity));
			}

			auto targetPrefab = _context.assetsManager.getAsset<Prefab>("prefabs/target.xml");
			auto targetEntity = targetPrefab->instantiate(_context);
			targetEntity->getComponent<components::Transform>()->setPosition(sf::Vector2f{ (map.target.column + 0.5f) * CELL_SIZE, (map.target.row + 0.5f) * CELL_SIZE });
			_entities.insert(std::move(targetEntity));

			auto cameraPrefab = _context.assetsManager.getAsset<Prefab>("prefabs/camera.xml");
			auto cameraEntity = cameraPrefab->instantiate(_context);
			cameraEntity->getComponent<components::Camera>()->setActive();
			cameraEntity->getComponent<components::Transform>()->setPosition(sf::Vector2f{ map.columns * (CELL_SIZE / 2.f), map.rows * (CELL_SIZE / 2.f) });
			_entities.insert(std::move(cameraEntity));
		}

		void Manager::onCharacterMoved(const backend::Character &character)
		{
			auto it = _entityByIds.find(character.id);
			assert(it != std::end(_entityByIds));
			auto entity = it->second;
			updateEntityTransform(*entity, character);
		}

		void Manager::removeEntities()
		{
			_entities.clear();
			_entityByIds.clear();
		}

		void Manager::updateEntityTransform(Entity & entity, const backend::Character & character)
		{
			auto transform = entity.getComponent<components::Transform>();
			transform->setPosition(sf::Vector2f{ (character.position.column + 0.5f) * CELL_SIZE, (character.position.row + 0.5f) * CELL_SIZE });
			transform->setRotation((int)character.orientation * 90.f);
		}
	}
}
