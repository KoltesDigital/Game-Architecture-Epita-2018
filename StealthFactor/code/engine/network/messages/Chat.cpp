#include "Chat.hpp"

#include <engine/EventListener.hpp>
#include <engine/serialization/Serialize.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace network
	{
		namespace messages
		{
			void Chat::triggerEvent(EventListener &listener)
			{
				listener.onChat(text);
			}
		}
	}

	namespace serialization
	{
		template <>
		void serialize<network::messages::Chat>(network::messages::Chat &message, serialization::Serializer &serializer)
		{
			serializer.declare("text", message.text);
		}

		template <>
		std::string getClassName<network::messages::Chat>()
		{
			return "chat";
		}
	}
}
