#pragma once

#include <SFML/Graphics/Transform.hpp>

namespace engine
{
	namespace graphics
	{
		class Camera
		{
		public:
			const sf::Vector2f &getPosition() const;
			void setPosition(const sf::Vector2f &position);

			// FOV, near/far planes...

		private:
			sf::Vector2f _position;
		};
	}
}
