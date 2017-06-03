#include "Message.hpp"

#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace network
	{
		void Message::triggerEvent(EventListener &)
		{
			assert(false);
		}
	}

	namespace serialization
	{
		template <>
		void serialize<network::Message>(network::Message &, serialization::Serializer &)
		{
		}

		template <>
		std::string getClassName<network::Message>()
		{
			assert(false);
			return "";
		}
	}
}
