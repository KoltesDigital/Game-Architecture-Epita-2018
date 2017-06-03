#pragma once

namespace engine
{
	class EventListener;

	namespace network
	{
		struct Message
		{
			virtual ~Message() = default;

			virtual void triggerEvent(EventListener &listener);
		};
	}
}
