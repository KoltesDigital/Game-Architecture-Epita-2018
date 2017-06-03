#include "PacketSaver.hpp"

#include <engine/serialization/TypeRegistry.h>

namespace engine
{
	namespace serialization
	{
		PacketSaver::PacketSaver(sf::Packet & packet, const TypeRegistry * registry)
			: _packet{ packet }
			, _registry{ registry }
		{
		}

		bool PacketSaver::beginName(const std::string &)
		{
			return true;
		}

		void PacketSaver::endName()
		{
		}

		void PacketSaver::process(void *value, const TypeInfo &typeInfo)
		{
			switch (typeInfo.type)
			{
			case Type::UnsignedChar:
				_packet << *reinterpret_cast<unsigned char *>(value);
				break;

			case Type::Int:
				_packet << *reinterpret_cast<int *>(value);
				break;

			case Type::Float:
				_packet << *reinterpret_cast<float *>(value);
				break;

			case Type::String:
				_packet << *reinterpret_cast<std::string *>(value);
				break;

			case Type::Vector:
			{
				auto methods{ reinterpret_cast<VectorMethods *>(typeInfo.methods) };
				auto &itemTypeInfo{ methods->getItemTypeInfo() };

				int size = methods->getSize(value);
				_packet << size;

				for (int i = 0; i < size; ++i)
				{
					process(methods->getValueAt(value, i), itemTypeInfo);
				}
				break;
			}

			case Type::SerializablePtr:
			{
				auto methods{ reinterpret_cast<SerializableMethods *>(typeInfo.methods) };
				_packet << methods->getClassName();
				Serializer::process(value, typeInfo);
				break;
			}

			default:
				Serializer::process(value, typeInfo);
				break;
			}
		}
}
}
