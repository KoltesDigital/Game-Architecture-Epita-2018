#include "PhysicsManager.hpp"

#include <cassert>
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
				assert(dSpaceGetNumGeoms(_spaceId) == 0);
				dSpaceDestroy(_spaceId);
			}

			dCloseODE();
		}

		void Manager::update()
		{
			_frameCollisions.clear();
			dSpaceCollide(_spaceId, &_frameCollisions, &Manager::nearCallback);
		}

		dGeomID Manager::createCollisionBox(gameplay::Entity *entity, float width, float height)
		{
			auto id = dCreateBox(_spaceId, width, height, 1.f);
			dGeomSetData(id, entity);
			return id;
		}

		void Manager::destroyCollisionVolume(dGeomID id)
		{
			dGeomDestroy(id);
		}

		std::set<gameplay::Entity *> Manager::getCollisionsWith(dGeomID object) const
		{
			std::set<gameplay::Entity *> entityCollisions;

			for (auto &collision : _frameCollisions)
			{
				if (collision.o1 == object)
				{
					entityCollisions.insert(reinterpret_cast<gameplay::Entity *>(dGeomGetData(collision.o2)));
				}
				if (collision.o2 == object)
				{
					entityCollisions.insert(reinterpret_cast<gameplay::Entity *>(dGeomGetData(collision.o1)));
				}
			}

			return entityCollisions;
		}

		void Manager::nearCallback(void *data, dGeomID o1, dGeomID o2)
		{
			auto &_frameCollisions = *reinterpret_cast<Collisions *>(data);
			_frameCollisions.emplace_back(o1, o2);
		}
	}
}
