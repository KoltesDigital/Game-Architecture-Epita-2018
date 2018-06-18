#pragma once

namespace engine
{
	namespace serialization
	{
		class Serializer;

		template <typename T>
		void serialize(T &, Serializer &serializer);
	}
}
