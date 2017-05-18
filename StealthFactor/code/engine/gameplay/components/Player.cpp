#include "Player.hpp"

#include <cassert>
#include <ode/collision.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <engine/input/InputManager.hpp>
#include <engine/physics/PhysicsManager.hpp>
#include <engine/gameplay/Entity.hpp>
#include <engine/gameplay/EntityContext.hpp>
#include <engine/gameplay/GameplayManager.hpp>
#include <engine/gameplay/components/CollisionBox.hpp>
#include <engine/gameplay/components/Target.hpp>
#include <engine/gameplay/components/Transform.hpp>

namespace engine
{
	namespace gameplay
	{
		namespace components
		{
			Player::Player(Entity &entity)
				: Component{ entity }
			{
			}

			void Player::update()
			{
				auto transform = getEntity().getComponent<Transform>();
				auto &inputManager = getEntity().getContext().inputManager;

				_justMoved = false;
				auto position = transform->getPosition();
				float rotation = transform->getRotation();

				if (inputManager.isKeyJustPressed(sf::Keyboard::Left))
				{
					_justMoved = true;
					position.x -= gameplay::Manager::CELL_SIZE;
					rotation = 180.f;
				}

				if (inputManager.isKeyJustPressed(sf::Keyboard::Right))
				{
					_justMoved = true;
					position.x += gameplay::Manager::CELL_SIZE;
					rotation = 0.f;
				}

				if (inputManager.isKeyJustPressed(sf::Keyboard::Up))
				{
					_justMoved = true;
					position.y -= gameplay::Manager::CELL_SIZE;
					rotation = -90.f;
				}

				if (inputManager.isKeyJustPressed(sf::Keyboard::Down))
				{
					_justMoved = true;
					position.y += gameplay::Manager::CELL_SIZE;
					rotation = 90.f;
				}

				if (_justMoved)
				{
					transform->setPosition(position);
					transform->setRotation(rotation);
				}

				auto collisions = getEntity().getComponent<CollisionBox>()->getCollisions();
				for (auto &entity : collisions)
				{
					auto targetComponent = entity->getComponent<Target>();
					if (targetComponent)
					{
						getEntity().getContext().entityListener.loadNextMap();
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
