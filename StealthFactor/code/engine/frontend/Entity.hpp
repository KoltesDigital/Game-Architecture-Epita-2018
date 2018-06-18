#pragma once

#include <cassert>
#include <memory>
#include <set>

namespace engine
{
	namespace frontend
	{
		class Component;
		struct EntityContext;

		class Entity
		{
		public:
			Entity(EntityContext &context);
			virtual ~Entity() = default;

			void onTransformChange();

			EntityContext &getContext();
			const EntityContext &getContext() const;

			template <typename Component>
			Component &addComponent();

			template <typename Component>
			Component *getComponent() const;

		private:
			using ComponentPtr = std::unique_ptr<Component>;
			using ComponentSet = std::set<ComponentPtr>;

			EntityContext &_context;

			ComponentSet _components;
		};

		template <typename Component>
		inline Component &Entity::addComponent()
		{
			assert(getComponent<Component>() == nullptr);
			auto component{ new Component(*this) };
			_components.insert(ComponentPtr{ component });
			return *component;
		}

		template <typename Component>
		inline Component *Entity::getComponent() const
		{
			auto it = std::find_if(
				std::cbegin(_components),
				std::cend(_components),
				[](auto &component)
			{
				return dynamic_cast<Component *>(component.get());
			});

			if (it != std::cend(_components))
			{
				return reinterpret_cast<Component *>(it->get());
			}

			return nullptr;
		}
	}
}
