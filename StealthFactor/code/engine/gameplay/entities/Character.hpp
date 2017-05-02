#pragma once

#include <ode/collision.h>
#include <engine/graphics/ShapeListId.hpp>
#include <engine/gameplay/Entity.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			class Character : public Entity
			{
			public:
				Character(EntityContext &context);
				virtual ~Character();

				void propagateTransform();

			protected:
				graphics::ShapeListId _shapeListId;
				dGeomID _collisionGeomId;

				bool _isWalking{ false };
			};
		}
	}
}
