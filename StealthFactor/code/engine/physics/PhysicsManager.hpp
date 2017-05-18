#pragma once

#include <vector>
#include <ode/collision.h>
#include <SFML/System/Vector2.hpp>
#include <engine/physics/CollisionEntities.hpp>

namespace engine
{
	namespace physics
	{
		class Manager
		{
		public:
			bool setUp();
			void tearDown();

			void update();

			dGeomID createCollisionBox(const gameplay::Entity &entity);
			void destroyCollisionVolume(dGeomID id);

			void setCollisionVolumePosition(dGeomID id, const sf::Vector2f &position);
			void setCollisionBoxSize(dGeomID id, const sf::Vector2f &size);

			EntitySet getCollisionsWith(dGeomID object) const;

		private:
			struct Collision
			{
				dGeomID o1;
				dGeomID o2;

				Collision(dGeomID o1, dGeomID o2);
			};

			using Collisions = std::vector<Collision>;

			dSpaceID _spaceId{};
			Collisions _frameCollisions;

			static void nearCallback(void *data, dGeomID o1, dGeomID o2);
		};
	}
}
