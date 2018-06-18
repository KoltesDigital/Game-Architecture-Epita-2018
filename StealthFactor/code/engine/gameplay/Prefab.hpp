#pragma once

#include <memory>
#include <vector>
#include <engine/assets/Asset.hpp>

namespace engine
{
	namespace gameplay
	{
		class Entity;
		struct EntityContext;

		struct PrefabComponent;

		struct Prefab : public assets::Asset
		{
			using ComponentPtr = std::unique_ptr<PrefabComponent>;
			using Components = std::vector<ComponentPtr>;

			Components components;

			Prefab();
			~Prefab();

			std::unique_ptr<Entity> instantiate(EntityContext &context) const;
		};
	}
}
