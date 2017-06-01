#include "Prefab.hpp"

#include <iostream>
#include <sstream>
#include <pugixml/pugixml.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/components/Camera.hpp>
#include <engine/gameplay/components/CollisionBox.hpp>
#include <engine/gameplay/components/Enemy.hpp>
#include <engine/gameplay/components/Player.hpp>
#include <engine/gameplay/components/Renderer.hpp>
#include <engine/gameplay/components/Target.hpp>
#include <engine/gameplay/components/Transform.hpp>
#include <engine/serialization/XMLLoader.hpp>

namespace engine
{
	namespace gameplay
	{
		Prefab::Prefab(const std::string &name)
			: _name{ name }
		{
		}

		std::unique_ptr<Entity> Prefab::instantiate(EntityContext &context) const
		{
			std::unique_ptr<Entity> entity;

			std::stringstream filename;
			filename << "prefabs/" << _name << ".xml";

			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_file(filename.str().c_str());

			if (result)
			{
				assert(!doc.empty());
				auto xmlMap = doc.first_child();

				entity = std::make_unique<Entity>(context);

				entity->addComponent<components::Transform>();

				for (auto &xmlElement : xmlMap.child("components").children())
				{
					if (!std::strcmp(xmlElement.name(), "camera"))
					{
						entity->addComponent<components::Camera>();
					}

					else if (!std::strcmp(xmlElement.name(), "collision_box"))
					{
						auto &collisionBox = entity->addComponent<components::CollisionBox>();

						float width = std::stof(xmlElement.child_value("width"));
						float height = std::stof(xmlElement.child_value("height"));

						collisionBox.setSize(sf::Vector2f{ width, height });
					}

					else if (!std::strcmp(xmlElement.name(), "enemy"))
					{
						auto &enemy = entity->addComponent<components::Enemy>();

						std::string archetypeName = xmlElement.child_value("archetype");
						serialization::XMLLoader loader{ archetypeName };
						if (loader.isLoaded())
						{
							Archetype archetype;
							archetype.serialize(loader);
							enemy.setArchetype(archetype);
						}
					}

					else if (!std::strcmp(xmlElement.name(), "player"))
					{
						entity->addComponent<components::Player>();
					}

					else if (!std::strcmp(xmlElement.name(), "renderer"))
					{
						auto &renderer = entity->addComponent<components::Renderer>();

						std::string shapelist = xmlElement.child_value("shapelist");

						renderer.setShapeListName(shapelist);
					}

					else if (!std::strcmp(xmlElement.name(), "target"))
					{
						entity->addComponent<components::Target>();
					}

					else
					{
						std::cerr << "Unknown component  [" << xmlElement.name() << "]." << std::endl;
					}
				}
			}
			else
			{
				std::cerr << "Prefab [" << _name << "] parsed with errors." << std::endl;
				std::cerr << "Error description: " << result.description() << std::endl;
				std::cerr << "Error offset: " << result.offset << std::endl;
			}

			return entity;
		}
	}
}
