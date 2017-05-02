#include "Character.hpp"

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
			Character::Character(EntityContext &context)
				: Entity{ context }
			{
				_collisionGeomId = _context.physicsManager.createCollisionBox(this, gameplay::Manager::CELL_SIZE * 0.9f, gameplay::Manager::CELL_SIZE * 0.9f);
				assert(_collisionGeomId);
			}

			Character::~Character()
			{
				_context.graphicsManager.destroyShapeListInstance(_shapeListId);
				_context.physicsManager.destroyCollisionVolume(_collisionGeomId);
			}

			void Character::propagateTransform()
			{
				_context.graphicsManager.setShapeListInstanceTransform(_shapeListId, getTransform());

				auto &position = getPosition();
				dGeomSetPosition(_collisionGeomId, position.x, position.y, 0);
			}
		}
	}
}
