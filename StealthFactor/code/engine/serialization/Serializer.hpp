#pragma once

#include <memory>
#include <string>
#include <engine/serialization/TypeInfo.hpp>

namespace engine
{
	namespace serialization
	{
		class Serializer
		{
		public:
			template <typename T>
			void declare(const std::string &name, T &value)
			{
				if (beginName(name))
				{
					process(&value, TypeInfoValue<T>::value);
					endName();
				}
			}

		protected:
			virtual bool beginName(const std::string &name) = 0;
			virtual void endName() = 0;
			virtual void process(void *value, const TypeInfo &typeInfo);
		};
	}
}
