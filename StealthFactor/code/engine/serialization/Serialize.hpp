#pragma once

#include <string>

namespace engine
{
	namespace serialization
	{
		class Serializer;

		template <typename T>
		void serialize(T &, Serializer &serializer);

		template <typename T>
		std::string getClassName();
	}
}
