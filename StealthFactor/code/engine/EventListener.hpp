#pragma once

#include <string>

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

		virtual void onChat(const std::string &text) = 0;
	};
}
