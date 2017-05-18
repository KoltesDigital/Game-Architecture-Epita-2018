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

		dGeomID Manager::createCollisionBox(const gameplay::Entity &entity)
		{
			auto id = dCreateBox(_spaceId, 0.f, 0., 0.f);
			dGeomSetData(id, const_cast<gameplay::Entity *>(&entity));
			return id;
		}

		void Manager::destroyCollisionVolume(dGeomID id)
		{
			dGeomDestroy(id);
		}

		void Manager::setCollisionVolumePosition(dGeomID id, const sf::Vector2f &position)
		{
			dGeomSetPosition(id, position.x, position.y, 0.f);
		}

		void Manager::setCollisionBoxSize(dGeomID id, const sf::Vector2f &size)
		{
			assert(dGeomGetClass(id) == dBoxClass);
			dGeomBoxSetLengths(id, size.x, size.y, 1.f);
		}

		EntitySet Manager::getCollisionsWith(dGeomID object) const
		{
			EntitySet entityCollisions;

			for (auto &collision : _frameCollisions)
			{
				if (collision.o1 == object)
				{
					entityCollisions.push_back(reinterpret_cast<const gameplay::Entity *>(dGeomGetData(collision.o2)));
				}
				if (collision.o2 == object)
				{
					entityCollisions.push_back(reinterpret_cast<const gameplay::Entity *>(dGeomGetData(collision.o1)));
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
