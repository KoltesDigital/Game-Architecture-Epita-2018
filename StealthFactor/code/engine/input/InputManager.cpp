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

			return _justPressedKeys.find(key) != std::cend(_justPressedKeys);
		}

		bool Manager::isKeyJustReleased(sf::Keyboard::Key key) const
		{
			if (!_active)
				return false;

			return _justReleasedKeys.find(key) != std::cend(_justReleasedKeys);
		}

		void Manager::clear()
		{
			_justPressedKeys.clear();
			_justReleasedKeys.clear();
		}

		void Manager::onKeyPressed(const sf::Event::KeyEvent &event)
		{
			_justPressedKeys.insert(event.code);
		}

		void Manager::onKeyReleased(const sf::Event::KeyEvent &event)
		{
			_justReleasedKeys.insert(event.code);
		}

		void Manager::setActive(bool active)
		{
			_active = active;
		}
	}
}
