#include "Component.hpp"

namespace engine
{
	namespace frontend
	{
		Component::Component(Entity &entity)
			: _entity{ entity }
		{
		}

		void Component::onTransformChange()
		{
		}

		Entity &Component::getEntity()
		{
			return _entity;
		}

		const Entity &Component::getEntity() const
		{
			return const_cast<Component *>(this)->getEntity();
		}
	}
}
