#include "PacketLoader.hpp"

#include <engine/serialization/TypeRegistry.h>

namespace engine
{
	namespace serialization
	{
		PacketLoader::PacketLoader(sf::Packet & packet, const TypeRegistry * registry)
			: _packet{ packet }
			, _registry{ registry }
		{
		}

		bool PacketLoader::beginName(const std::string &)
		{
			return true;
		}

		void PacketLoader::endName()
		{
		}

		void PacketLoader::process(void *value, const TypeInfo &typeInfo)
		{
			switch (typeInfo.type)
			{
			case Type::UnsignedChar:
				_packet >> *reinterpret_cast<unsigned char *>(value);
				break;

			case Type::Int:
				_packet >> *reinterpret_cast<int *>(value);
				break;

			case Type::Float:
				_packet >> *reinterpret_cast<float *>(value);
				break;

			case Type::String:
				_packet >> *reinterpret_cast<std::string *>(value);
				break;

			case Type::Vector:
			{
				auto methods{ reinterpret_cast<VectorMethods *>(typeInfo.methods) };
				auto &itemTypeInfo{ methods->getItemTypeInfo() };

				int size;
				_packet >> size;
				methods->setSize(value, size);

				for (int i = 0; i < size; ++i)
				{
					process(methods->getValueAt(value, i), itemTypeInfo);
				}
				break;
			}

			case Type::SerializablePtr:
			{
				std::string name;
				_packet >> name;

				if (_registry)
				{
					auto info{ _registry->getInfo(name) };
					if (info)
					{
						*reinterpret_cast<void **>(value) = info->create();
						Serializer::process(value, info->typeInfo);
					}
				}
				else
				{
					auto methods{ reinterpret_cast<SerializableMethods *>(typeInfo.methods) };
					*reinterpret_cast<void **>(value) = methods->create();
					Serializer::process(value, typeInfo);
				}
				break;
			}

			default:
				Serializer::process(value, typeInfo);
				break;
			}
		}
}
}
