#pragma once

#include <deque>
#include <map>
#include <memory>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Network/Packet.hpp>
#include <engine/serialization/PacketLoader.hpp>
#include <engine/serialization/PacketSaver.hpp>
#include <engine/serialization/TypeRegistry.h>

namespace engine
{
	namespace network
	{
		struct Message;

		class Manager
		{
		public:
			using MessagePtr = std::unique_ptr<Message>;

			Manager();
			~Manager();

			template <typename T>
			void broadcast(T &message);

			MessagePtr receive();



		private:
			serialization::TypeRegistry _messageTypeRegistry;

			struct Info
			{
				std::deque<sf::Packet> packets;
			};

			static sf::Mutex _mutex;
			static std::map<Manager *, Info> _infoByManagers;
		};

		template<typename T>
		inline void Manager::broadcast(T &message)
		{
			sf::Packet packet;
			serialization::PacketSaver saver{ packet , &_messageTypeRegistry };

			auto messagePtr{ &message };
			saver.processValue(messagePtr);

			sf::Lock lock{ _mutex };
			for (auto &it : _infoByManagers)
			{
				if (it.first != this)
				{
					it.second.packets.push_back(packet);
				}
			}
		}
	}
}
