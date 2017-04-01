#pragma once

#include <cstring>
#include <string>

namespace sf
{
	class Packet;
}

namespace engine
{
	namespace util
	{
		class StringId
		{
		public:
			StringId();
			explicit StringId(const std::string &str);

			bool operator ==(const StringId &other) const;
			bool operator <(const StringId &other) const;

#if !defined(DEBUG)
			operator std::size_t() const;
#endif

		private:
			std::size_t hash;

			static std::hash<std::string> hasher;

#ifdef DEBUG
		public:
			operator const std::string &() const;

		private:
			std::string str;
#endif
		};
	}
}
