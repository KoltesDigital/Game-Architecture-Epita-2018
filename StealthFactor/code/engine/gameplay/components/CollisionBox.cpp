#include "CollisionBox.hpp"

#include <cassert>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/components/Transform.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			CollisionBox::CollisionBox(Entity &entity)
				: Component{ entity }
			{
				_collisionGeomId = getPhysicsManager().createCollisionBox(getEntity());
				assert(_collisionGeomId);
			}

			CollisionBox::~CollisionBox()
			{
				getPhysicsManager().destroyCollisionVolume(_collisionGeomId);
			}

			void CollisionBox::onTransformChange()
			{
				auto transform = getEntity().getComponent<Transform>();
				auto &position = transform->getPosition();
				getPhysicsManager().setCollisionVolumePosition(_collisionGeomId, position);
			}

			void CollisionBox::setSize(const sf::Vector2f &size)
			{
				getPhysicsManager().setCollisionBoxSize(_collisionGeomId, size);
			}

			physics::EntitySet CollisionBox::getCollisions() const
			{
				return getPhysicsManager().getCollisionsWith(_collisionGeomId);
			}

			physics::Manager &CollisionBox::getPhysicsManager() const
			{
				return getEntity().getContext().physicsManager;
			}
		}
	}
}
