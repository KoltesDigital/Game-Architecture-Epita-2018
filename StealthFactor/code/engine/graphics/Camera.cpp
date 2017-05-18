#include "Camera.hpp"

namespace engine
{
	namespace graphics
	{
		const sf::Vector2f &Camera::getPosition() const
		{
			return _position;
		}

		void Camera::setPosition(const sf::Vector2f &position)
		{
			_position = position;
		}
	}
}
