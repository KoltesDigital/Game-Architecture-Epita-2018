#include "PhysicsManager.hpp"

#include <ode/odeinit.h>

namespace engine
{
	namespace physics
	{
		Manager::Collision::Collision(dGeomID o1, dGeomID o2)
			: o1{ o1 }
			, o2{ o2 }
		{
		}

		bool Manager::setUp()
		{
			dInitODE();

			_spaceId = dHashSpaceCreate(0);
			return _spaceId != nullptr;
		}

		void Manager::tearDown()
		{
			if (_spaceId != nullptr)
			{
				dSpaceDestroy(_spaceId);
			}

			dCloseODE();
		}

		void Manager::update()
		{
			_frameCollisions.clear();
			dSpaceCollide(_spaceId, &_frameCollisions, &Manager::nearCallback);
		}

		const dSpaceID Manager::getSpaceId() const
		{
			return _spaceId;
		}

		std::set<dGeomID> Manager::getCollisionsWith(dGeomID object) const
		{
			std::set<dGeomID> objectCollisions;

			for (auto &collision : _frameCollisions)
			{
				if (collision.o1 == object)
				{
					objectCollisions.insert(collision.o2);
				}
				if (collision.o2 == object)
				{
					objectCollisions.insert(collision.o1);
				}
			}

			return objectCollisions;
		}

		void Manager::nearCallback(void *data, dGeomID o1, dGeomID o2)
		{
			auto &_frameCollisions = *reinterpret_cast<Collisions *>(data);
			_frameCollisions.emplace_back(o1, o2);
		}
	}
}
