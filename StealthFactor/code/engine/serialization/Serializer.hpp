#pragma once

#include <string>

namespace engine
{
	namespace serialization
	{
		class Serializer
		{
		public:
			virtual void declare(const std::string &name, float &value) = 0;
			virtual void declare(const std::string &name, int &value) = 0;
			virtual void declare(const std::string &name, std::string &value) = 0;
		};
	}
}
