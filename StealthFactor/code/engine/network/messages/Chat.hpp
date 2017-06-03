#pragma once

#include <string>
#include <engine/network/Message.hpp>

namespace engine
{
	namespace network
	{
		namespace messages
		{
			struct Chat : Message
			{
				std::string text;

				void triggerEvent(EventListener &listener) override;
			};
		}
	}
}
