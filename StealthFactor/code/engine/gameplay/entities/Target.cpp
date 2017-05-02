#include "Target.hpp"

#include <cassert>
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
				_shapeListId = _context.graphicsManager.createShapeListInstance("target");
				assert(_shapeListId);

				_collisionGeomId = _context.physicsManager.createCollisionBox(this, gameplay::Manager::CELL_SIZE * 0.9f, gameplay::Manager::CELL_SIZE * 0.9f);
				assert(_collisionGeomId);
			}

			Target::~Target()
			{
				_context.graphicsManager.destroyShapeListInstance(_shapeListId);
				_context.physicsManager.destroyCollisionVolume(_collisionGeomId);
			}

			void Target::update()
			{
				propagateTransform();
			}

			void Target::propagateTransform()
			{
				_context.graphicsManager.setShapeListInstanceTransform(_shapeListId, getTransform());

				auto &position = getPosition();
				dGeomSetPosition(_collisionGeomId, position.x, position.y, 0);
			}
		}
	}
}
