#include "NetworkManager.hpp"

#include <SFML/System/Lock.hpp>
#include <engine/network/Message.hpp>
#include <engine/network/messages/Chat.hpp>
#include <engine/serialization/Serialize.hpp>

namespace engine
{
	namespace network
	{
		sf::Mutex Manager::_mutex;
		std::map<Manager *, Manager::Info> Manager::_infoByManagers;

		Manager::Manager()
		{
			_messageTypeRegistry.registerClass<messages::Chat>();

			sf::Lock lock{ _mutex };
			_infoByManagers.insert(std::make_pair(this, Info{}));
		}

		Manager::~Manager()
		{
			sf::Lock lock{ _mutex };
			_infoByManagers.erase(this);
		}

		Manager::MessagePtr Manager::receive()
		{
			sf::Packet packet;

			{
				sf::Lock lock{ _mutex };
				auto it = _infoByManagers.find(this);
				auto &packets = it->second.packets;
				if (packets.empty())
				{
					return MessagePtr{};
				}
				packet = packets.front();
				packets.pop_front();
			}

			Message *message;
			serialization::PacketLoader loader{ packet, &_messageTypeRegistry };
			loader.processValue(message);

			return MessagePtr{ message };
		}
	}
}
