#include "Serializer.hpp"

#include <cassert>

namespace engine
{
	namespace serialization
	{
		void Serializer::process(void *value, const TypeInfo &typeInfo)
		{
			switch (typeInfo.type)
			{
			case Type::Serializable:
			case Type::SerializablePtr:
			{
				auto methods{ reinterpret_cast<SerializableMethods *>(typeInfo.methods) };
				methods->serialize(value, *this);
				break;
			}

			default:
				assert(false);
				break;
			}
		}
	}
}
