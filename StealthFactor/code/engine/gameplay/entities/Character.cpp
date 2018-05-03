#include "Character.hpp"

#include <engine/gameplay/EntityContext.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Character::Character(EntityContext &context)
				: Entity{ context }
			{
				_collisionGeomId = dCreateBox(context.physicsManager.getSpaceId(), 0.f, 0.f, 0.f);
				dGeomSetData(_collisionGeomId, this);
			}

			Character::~Character()
			{
				dGeomDestroy(_collisionGeomId);
			}

			void Character::draw()
			{
				_context.graphicsManager.draw(_shapeList, getTransform());
			}
		}
	}
}
