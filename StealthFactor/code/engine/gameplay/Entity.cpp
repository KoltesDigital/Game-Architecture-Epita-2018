#include "Entity.hpp"

#include <engine/gameplay/Component.hpp>

namespace engine
{
	namespace gameplay
	{
		Entity::Entity(EntityContext &context)
			: _context{ context }
		{
		}

		void Entity::update()
		{
			for (auto &component : _components)
			{
				component->update();
			}
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
