#include "PhysicsManager.hpp"

#include <ode/odeinit.h>

namespace engine
{
	namespace physics
	{
		Manager *Manager::instance = nullptr;

		Manager::Collision::Collision(dGeomID o1, dGeomID o2)
			: o1{ o1 }
			, o2{ o2 }
		{
		}

		Manager::Manager()
		{
			dInitODE();

			spaceId = dHashSpaceCreate(0);
		}

		Manager::~Manager()
		{
			dSpaceDestroy(spaceId);
			dCloseODE();
		}

		void Manager::update()
		{
			frameCollisions.clear();
			dSpaceCollide(spaceId, &frameCollisions, &Manager::nearCallback);
		}

		const dSpaceID Manager::getSpaceId() const
		{
			return spaceId;
		}

		std::set<dGeomID> Manager::getCollisionsWith(dGeomID object) const
		{
			std::set<dGeomID> objectCollisions;

			for (auto &collision : frameCollisions)
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
			auto &frameCollisions = *reinterpret_cast<Collisions *>(data);
			frameCollisions.emplace_back(o1, o2);
		}

		Manager &Manager::getInstance()
		{
			if (!instance)
				instance = new Manager();

			return *instance;
		}
	}
}
