#pragma once

#include <SFML/System/Vector2.hpp>

namespace engine
{
	namespace graphics
	{
		class ViewProvider
		{
		public:
			virtual sf::Vector2f getViewCenter() const = 0;
		};
	}
}
