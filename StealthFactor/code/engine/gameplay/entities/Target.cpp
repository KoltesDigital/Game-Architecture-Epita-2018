#include "Target.hpp"

#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/graphics/GraphicsManager.hpp>
#include <engine/physics/PhysicsManager.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Target::Target(EntityContext &context)
				: Entity{ context }
			{
				_shapeList.load("target");

				_collisionGeomId = dCreateBox(context.physicsManager.getSpaceId(), gameplay::Manager::CELL_SIZE * 0.9f, gameplay::Manager::CELL_SIZE * 0.9f, 1.f);
				dGeomSetData(_collisionGeomId, this);
			}

			Target::~Target()
			{
				dGeomDestroy(_collisionGeomId);
			}

			void Target::update()
			{
				auto &position = getPosition();
				dGeomSetPosition(_collisionGeomId, position.x, position.y, 0);
			}

			void Target::draw()
			{
				_context.graphicsManager.draw(_shapeList, getTransform());
			}
		}
	}
}
