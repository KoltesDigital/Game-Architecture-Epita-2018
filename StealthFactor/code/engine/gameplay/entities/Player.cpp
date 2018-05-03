#include "engine/gameplay/entities/Player.hpp"

#include <ode/collision.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/entities/Target.hpp>
#include <engine/Engine.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace entities
		{
			Player::Player(EntityContext &context)
				: Character{ context }
			{
				_shapeList.load("player");

				_collisionGeomId = dCreateBox(context.physicsManager.getSpaceId(), gameplay::Manager::CELL_SIZE * 0.9f, gameplay::Manager::CELL_SIZE * 0.9f, 1.f);
				dGeomSetData(_collisionGeomId, this);
			}

			void Player::update()
			{
				_justMoved = false;
				auto position = getPosition();
				float rotation = getRotation();

				if (_context.inputManager.isKeyJustPressed(sf::Keyboard::Left))
				{
					_justMoved = true;
					position.x -= gameplay::Manager::CELL_SIZE;
					rotation = 180.f;
				}

				if (_context.inputManager.isKeyJustPressed(sf::Keyboard::Right))
				{
					_justMoved = true;
					position.x += gameplay::Manager::CELL_SIZE;
					rotation = 0.f;
				}

				if (_context.inputManager.isKeyJustPressed(sf::Keyboard::Up))
				{
					_justMoved = true;
					position.y -= gameplay::Manager::CELL_SIZE;
					rotation = -90.f;
				}

				if (_context.inputManager.isKeyJustPressed(sf::Keyboard::Down))
				{
					_justMoved = true;
					position.y += gameplay::Manager::CELL_SIZE;
					rotation = 90.f;
				}

				if (_justMoved)
				{
					setPosition(position);
					setRotation(rotation);

					dGeomSetPosition(_collisionGeomId, position.x, position.y, 0);
				}

				auto collisions = _context.physicsManager.getCollisionsWith(_collisionGeomId);
				for (auto &geomId : collisions)
				{
					auto entity = reinterpret_cast<Entity *>(dGeomGetData(geomId));
					auto targetEntity = dynamic_cast<entities::Target *>(entity);
					if (targetEntity)
					{
						_context.entityListener.loadNextMap();
					}
				}
			}

			bool Player::hasJustMoved() const
			{
				return _justMoved;
			}
		}
	}
}
