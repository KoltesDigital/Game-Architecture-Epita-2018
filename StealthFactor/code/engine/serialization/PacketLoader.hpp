#pragma once

#include <vector>
#include <SFML/Network/Packet.hpp>
#include <engine/serialization/Serializer.hpp>

namespace engine
{
	namespace serialization
	{
		class TypeRegistry;

		class PacketLoader : public Serializer
		{
		public:
			PacketLoader(sf::Packet &packet, const TypeRegistry *registry = nullptr);

		protected:
			// Serializer
			bool beginName(const std::string &name) override;
			void endName() override;
			void process(void *value, const TypeInfo &typeInfo) override;

		private:
			const TypeRegistry *_registry;

			sf::Packet &_packet;
		};
	}
}
