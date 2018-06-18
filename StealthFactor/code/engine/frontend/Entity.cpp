#include "Entity.hpp"

#include <engine/frontend/Component.hpp>

namespace engine
{
	namespace frontend
	{
		Entity::Entity(EntityContext &context)
			: _context{ context }
		{
		}

		void Entity::onTransformChange()
		{
			for (auto &component : _components)
			{
				component->onTransformChange();
			}
		}

		EntityContext &Entity::getContext()
		{
			return _context;
		}

		const EntityContext &Entity::getContext() const
		{
			return const_cast<Entity *>(this)->getContext();
		}
	}
}
