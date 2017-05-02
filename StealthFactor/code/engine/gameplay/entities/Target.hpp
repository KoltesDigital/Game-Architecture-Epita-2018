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
			class Target : public Entity
			{
			public:
				Target(EntityContext &context);
				~Target();

				virtual void update() override;

				void propagateTransform();

			private:
				graphics::ShapeListId _shapeListId;
				dGeomID _collisionGeomId;
			};
		}
	}
}
