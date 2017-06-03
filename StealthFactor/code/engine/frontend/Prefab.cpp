#include "Prefab.hpp"

#include <cassert>
#include <engine/assets/AssetsManager.hpp>
#include <engine/frontend/Entity.hpp>
#include <engine/frontend/EntityContext.hpp>
#include <engine/frontend/components/Camera.hpp>
#include <engine/frontend/components/Renderer.hpp>
#include <engine/frontend/components/Transform.hpp>
#include <engine/serialization/XMLLoader.hpp>

namespace engine
{
	namespace frontend
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

			struct Renderer : public PrefabComponent
			{
				std::string shapelistName;

				void instantiate(Entity &entity, EntityContext &) const override
				{
					auto &renderer = entity.addComponent<components::Renderer>();
					renderer.setShapeListName(shapelistName);
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
		struct AssetTypeRegistry<frontend::Prefab>
		{
			static serialization::TypeRegistry value;

			static struct Init
			{
				Init()
				{
					value.registerClass<frontend::prefabComponents::Camera>();
					value.registerClass<frontend::prefabComponents::Renderer>();
				}
			} init;
		};

		serialization::TypeRegistry AssetTypeRegistry<frontend::Prefab>::value;
		AssetTypeRegistry<frontend::Prefab>::Init AssetTypeRegistry<frontend::Prefab>::init;
	}

	namespace serialization
	{
		template <>
		void serialize<frontend::PrefabComponent>(frontend::PrefabComponent &, serialization::Serializer &)
		{
		}

		template <>
		std::string getClassName<frontend::PrefabComponent>()
		{
			assert(false);
			return "";
		}

		template <>
		void serialize<frontend::prefabComponents::Camera>(frontend::prefabComponents::Camera &camera, serialization::Serializer &serializer)
		{
			serialize(static_cast<frontend::PrefabComponent &>(camera), serializer);
		}

		template <>
		std::string getClassName<frontend::prefabComponents::Camera>()
		{
			return "camera";
		}

		template <>
		void serialize<frontend::prefabComponents::Renderer>(frontend::prefabComponents::Renderer &renderer, serialization::Serializer &serializer)
		{
			serialize(static_cast<frontend::PrefabComponent &>(renderer), serializer);
			serializer.declare("shapelist", renderer.shapelistName);
		}

		template <>
		std::string getClassName<frontend::prefabComponents::Renderer>()
		{
			return "renderer";
		}

		template <>
		void serialize<frontend::Prefab>(frontend::Prefab &prefab, serialization::Serializer &serializer)
		{
			serializer.declare("components", prefab.components);
		}
	}
}
