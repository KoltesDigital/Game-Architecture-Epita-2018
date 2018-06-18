#include "Prefab.hpp"

#include <cassert>
#include <engine/assets/AssetsManager.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.hpp>
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
		struct PrefabComponent
		{
			virtual void instantiate(Entity &, EntityContext &) const
			{
				assert(false);
			}
		};

		namespace prefabComponents
		{
			struct Camera : public PrefabComponent
			{
				void instantiate(Entity &entity, EntityContext &) const override
				{
					entity.addComponent<components::Camera>();
				}
			};

			struct CollisionBox : public PrefabComponent
			{
				float width;
				float height;

				void instantiate(Entity &entity, EntityContext &) const override
				{
					auto &collisionBox = entity.addComponent<components::CollisionBox>();
					collisionBox.setSize(sf::Vector2f{ width, height });
				}
			};

			struct Enemy : public PrefabComponent
			{
				std::string archetypeName;

				void instantiate(Entity &entity, EntityContext &context) const override
				{
					auto &enemy = entity.addComponent<components::Enemy>();

					auto archetype{ context.assetsManager.getAsset<Archetype>(archetypeName) };
					if (archetype)
					{
						enemy.setArchetype(*archetype);
					}
				}
			};

			struct Player : public PrefabComponent
			{
				void instantiate(Entity &entity, EntityContext &) const override
				{
					entity.addComponent<components::Player>();
				}
			};

			struct Renderer : public PrefabComponent
			{
				std::string shapelistName;

				void instantiate(Entity &entity, EntityContext &) const override
				{
					auto &renderer = entity.addComponent<components::Renderer>();
					renderer.setShapeListName(shapelistName);
				}
			};

			struct Target : public PrefabComponent
			{
				void instantiate(Entity &entity, EntityContext &) const override
				{
					entity.addComponent<components::Target>();
				}
			};
		}

		Prefab::Prefab()
		{
		}

		Prefab::~Prefab()
		{
		}

		std::unique_ptr<Entity> Prefab::instantiate(EntityContext &context) const
		{
			auto entity{ std::make_unique<Entity>(context) };

			entity->addComponent<components::Transform>();

			for (auto &component : components)
			{
				component->instantiate(*entity, context);
			}

			return entity;
		}
	}

	namespace assets
	{
		template <>
		struct AssetTypeRegistry<gameplay::Prefab>
		{
			static serialization::TypeRegistry value;

			static struct Init
			{
				Init()
				{
					value.registerClass<gameplay::prefabComponents::Camera>("camera");
					value.registerClass<gameplay::prefabComponents::CollisionBox>("collision_box");
					value.registerClass<gameplay::prefabComponents::Enemy>("enemy");
					value.registerClass<gameplay::prefabComponents::Player>("player");
					value.registerClass<gameplay::prefabComponents::Renderer>("renderer");
					value.registerClass<gameplay::prefabComponents::Target>("target");
				}
			} init;
		};

		serialization::TypeRegistry AssetTypeRegistry<gameplay::Prefab>::value;
		AssetTypeRegistry<gameplay::Prefab>::Init AssetTypeRegistry<gameplay::Prefab>::init;
	}

	namespace serialization
	{
		template <>
		void serialize<gameplay::PrefabComponent>(gameplay::PrefabComponent &, serialization::Serializer &)
		{
		}

		template <>
		void serialize<gameplay::prefabComponents::Camera>(gameplay::prefabComponents::Camera &camera, serialization::Serializer &serializer)
		{
			serialize(static_cast<gameplay::PrefabComponent &>(camera), serializer);
		}

		template <>
		void serialize<gameplay::prefabComponents::CollisionBox>(gameplay::prefabComponents::CollisionBox &collisionBox, serialization::Serializer &serializer)
		{
			serialize(static_cast<gameplay::PrefabComponent &>(collisionBox), serializer);
			serializer.declare("width", collisionBox.width);
			serializer.declare("height", collisionBox.height);
		}

		template <>
		void serialize<gameplay::prefabComponents::Enemy>(gameplay::prefabComponents::Enemy &enemy, serialization::Serializer &serializer)
		{
			serialize(static_cast<gameplay::PrefabComponent &>(enemy), serializer);
			serializer.declare("archetype", enemy.archetypeName);
		}

		template <>
		void serialize<gameplay::prefabComponents::Player>(gameplay::prefabComponents::Player &player, serialization::Serializer &serializer)
		{
			serialize(static_cast<gameplay::PrefabComponent &>(player), serializer);
		}

		template <>
		void serialize<gameplay::prefabComponents::Renderer>(gameplay::prefabComponents::Renderer &renderer, serialization::Serializer &serializer)
		{
			serialize(static_cast<gameplay::PrefabComponent &>(renderer), serializer);
			serializer.declare("shapelist", renderer.shapelistName);
		}

		template <>
		void serialize<gameplay::prefabComponents::Target>(gameplay::prefabComponents::Target &target, serialization::Serializer &serializer)
		{
			serialize(static_cast<gameplay::PrefabComponent &>(target), serializer);
		}

		template <>
		void serialize<gameplay::Prefab>(gameplay::Prefab &prefab, serialization::Serializer &serializer)
		{
			serializer.declare("components", prefab.components);
		}
	}
}
