#include "Enemy.hpp"

#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/entities/Player.hpp>
#include <engine/graphics/GraphicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Enemy::Enemy(EntityContext &context, const std::string &archetypeName)
				: Character{ context }
			{
				loadArchetype(archetypeName);
			}

			void Enemy::update()
			{
				auto &player = _context.entityListener.getPlayer();
				if (player.hasJustMoved())
				{
					auto &playerPosition = player.getPosition();
					auto &myPosition = getPosition();

					auto offset = myPosition - playerPosition;
					offset /= gameplay::Manager::CELL_SIZE;
					float distance2 = offset.x * offset.x + offset.y * offset.y;
					if (distance2 <= _visionRadius * _visionRadius)
					{
						if (_shootDelayCounter < _shootDelay)
						{
							++_shootDelayCounter;
						}
						else
						{
							_context.entityListener.gameOver();
						}
					}
					else
					{
						_shootDelayCounter = 0;
					}
				}
			}

			void Enemy::loadArchetype(const std::string &archetypeName)
			{
				std::stringstream filename;
				filename << "archetypes/" << archetypeName << ".xml";

				pugi::xml_document doc;
				pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

				if (result)
				{
					assert(!doc.empty());
					auto xmlArchetype = doc.first_child();

					std::string shapeListName = xmlArchetype.child_value("shapelist");
					_shapeListId = _context.graphicsManager.createShapeListInstance(shapeListName);
					assert(_shapeListId);

					_visionRadius = std::stof(xmlArchetype.child_value("vision_radius"));
					assert(_visionRadius > 0.f);

					_shootDelay = std::stoi(xmlArchetype.child_value("shoot_delay"));
					assert(_shootDelay >= 0);
				}
				else
				{
					std::cerr << "Archetype [" << archetypeName << "] parsed with errors." << std::endl;
					std::cerr << "Error description: " << result.description() << std::endl;
					std::cerr << "Error offset: " << result.offset << std::endl;
				}
			}
		}
	}
}
