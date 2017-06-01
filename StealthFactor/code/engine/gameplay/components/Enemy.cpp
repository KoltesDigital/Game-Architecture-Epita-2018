#include "Enemy.hpp"

#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/EntityListener.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/components/Player.hpp>
#include <engine/gameplay/components/Renderer.hpp>
#include <engine/gameplay/components/Transform.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			Enemy::Enemy(Entity &entity)
				: Component{ entity }
			{
			}

			void Enemy::update()
			{
				if (_archetypeHasChanged)
				{
					_archetypeHasChanged = false;
					getEntity().getComponent<Renderer>()->setShapeListName(_archetype.shapeListName);
				}

				auto &player = getEntity().getContext().entityListener.getPlayer();
				if (player.hasJustMoved())
				{
					auto &playerPosition = player.getEntity().getComponent<Transform>()->getPosition();
					auto &myPosition = getEntity().getComponent<Transform>()->getPosition();

					auto offset = myPosition - playerPosition;
					offset /= gameplay::Manager::CELL_SIZE;
					float distance2 = offset.x * offset.x + offset.y * offset.y;
					if (distance2 <= _archetype.visionRadius * _archetype.visionRadius)
					{
						if (_shootDelayCounter < _archetype.shootDelay)
						{
							++_shootDelayCounter;
						}
						else
						{
							getEntity().getContext().entityListener.gameOver();
						}
					}
					else
					{
						_shootDelayCounter = 0;
					}
				}
			}

			void Enemy::setArchetype(const Archetype &archetype)
			{
				_archetype = archetype;
				_archetypeHasChanged = true;
			}
		}
	}
}
