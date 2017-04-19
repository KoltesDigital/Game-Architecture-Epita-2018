#include "engine/input/InputManager.hpp"

#include <engine/graphics/GraphicsManager.hpp>

namespace engine
{
	namespace input
	{
		bool Manager::isKeyPressed(sf::Keyboard::Key key) const
		{
			if (!_active)
				return false;

			return sf::Keyboard::isKeyPressed(key);
		}

		bool Manager::isKeyJustPressed(sf::Keyboard::Key key) const
		{
			if (!_active)
				return false;

			return justPressedKeys.find(key) != std::cend(justPressedKeys);
		}

		bool Manager::isKeyJustReleased(sf::Keyboard::Key key) const
		{
			if (!_active)
				return false;

			return justReleasedKeys.find(key) != std::cend(justReleasedKeys);
		}

		void Manager::clear()
		{
			justPressedKeys.clear();
			justReleasedKeys.clear();
		}

		void Manager::onKeyPressed(const sf::Event::KeyEvent &event)
		{
			justPressedKeys.insert(event.code);
		}

		void Manager::onKeyReleased(const sf::Event::KeyEvent &event)
		{
			justReleasedKeys.insert(event.code);
		}

		void Manager::setActive(bool active)
		{
			_active = active;
		}
	}
}
