#include "Player.hpp"

#include <engine/input/InputManager.hpp>
#include <engine/backend/Character.hpp>
#include <engine/backend/ControlContext.hpp>
#include <engine/backend/ControlListener.hpp>

namespace engine
{
	namespace backend
	{
		namespace controls
		{
			Player::Player(Character &character, ControlContext &context)
				: Control{ character, context }
			{
			}

			void Player::update()
			{
				auto &character = getCharacter();
				auto &inputManager = getContext().inputManager;

				bool justMoved = false;

				if (inputManager.isKeyJustPressed(sf::Keyboard::Left))
				{
					justMoved = true;
					character.position.column -= 1;
					character.orientation = Orientation::Left;
				}

				if (inputManager.isKeyJustPressed(sf::Keyboard::Right))
				{
					justMoved = true;
					character.position.column += 1;
					character.orientation = Orientation::Right;
				}

				if (inputManager.isKeyJustPressed(sf::Keyboard::Up))
				{
					justMoved = true;
					character.position.row -= 1;
					character.orientation = Orientation::Top;
				}

				if (inputManager.isKeyJustPressed(sf::Keyboard::Down))
				{
					justMoved = true;
					character.position.row += 1;
					character.orientation = Orientation::Bottom;
				}

				if (justMoved)
				{
					getContext().controlListener.characterMoved(getCharacter());
				}
			}

			std::string Player::getPrefabName() const
			{
				return "prefabs/player.xml";
			}
		}
	}
}
