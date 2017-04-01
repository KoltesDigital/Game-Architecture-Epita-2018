#include "Character.hpp"

#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Character::Character()
			{
				collisionGeomId = dCreateBox(physics::Manager::getInstance().getSpaceId(), 0.f, 0.f, 0.f);
				dGeomSetData(collisionGeomId, this);
			}

			Character::~Character()
			{
				dGeomDestroy(collisionGeomId);
			}

			void Character::draw()
			{
				graphics::Manager::getInstance().draw(shapeList, getTransform());
			}
		}
	}
}
