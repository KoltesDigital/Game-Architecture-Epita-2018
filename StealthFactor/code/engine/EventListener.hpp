#pragma once

namespace sf
{
	class Event;
}

namespace engine
{
	class EventListener
	{
	public:
		virtual void onEvent(const sf::Event &event) = 0;
	};
}
