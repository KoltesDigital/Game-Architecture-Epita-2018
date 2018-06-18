#include <SFML/Graphics/Color.hpp>
#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace serialization
	{
		template <>
		void serialize<sf::Color>(sf::Color &color, Serializer &serializer)
		{
			serializer.declare("r", color.r);
			serializer.declare("g", color.g);
			serializer.declare("b", color.b);
		}
	}
}
