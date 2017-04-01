#pragma once

#include <set>
#include <vector>
#include <ode/collision.h>

namespace engine
{
	namespace physics
	{
		class Manager
		{
		public:
			struct Collision
			{
				dGeomID o1;
				dGeomID o2;

				Collision(dGeomID o1, dGeomID o2);
			};

			using Collisions = std::vector<Collision>;

			Manager();
			~Manager();

			void update();

			const dSpaceID getSpaceId() const;

			std::set<dGeomID> getCollisionsWith(dGeomID object) const;

			static Manager &getInstance();

		private:
			dSpaceID spaceId;
			Collisions frameCollisions;

			static void nearCallback(void *data, dGeomID o1, dGeomID o2);

			static Manager *instance;
		};
	}
}
