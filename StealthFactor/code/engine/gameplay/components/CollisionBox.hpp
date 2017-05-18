#pragma once

#include <ode/collision.h>
#include <SFML/System/Vector2.hpp>
#include <engine/physics/CollisionEntities.hpp>
#include <engine/gameplay/Component.hpp>

namespace engine
{
	namespace physics
	{
		class Manager;
	}

	namespace gameplay
	{
		namespace components
		{
			class CollisionBox : public Component
			{
			public:
				CollisionBox(Entity &entity);
				virtual ~CollisionBox();

				void onTransformChange() override;

				void setSize(const sf::Vector2f &size);

				physics::EntitySet getCollisions() const;

			protected:
				physics::Manager &getPhysicsManager() const;

			private:
				dGeomID _collisionGeomId;
			};
		}
	}
}
